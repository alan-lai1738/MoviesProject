#include "Store.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Store::Store() { inv = new Inventory(); }

void Store::fillCustomerDatabase(const string &fileName) {
  ifstream in(fileName);
  string line; // Line were reading
  if (!in) {
    cout << "Can't open file " << fileName << endl;
  }

  while (!in.eof()) {
    getline(in, line);
    if (line.empty()) {
      break;
    }
    istringstream parseLine(line);
    int custID;
    string first, last;
    parseLine >> custID;
    parseLine >> first >> last;
    Customer *c = new Customer(first, last, custID);
    customerDatabase.put(custID, c);
  }
  in.close();
}

void Store::stockDVDShelves(const string &fileName) {
  ifstream in(fileName);
  string line; // Line were reading
  if (!in) {
    cout << "Can't open file " << fileName << endl;
  }

  while (!in.eof()) {
    getline(in, line);
    if (line.empty()) {
      break;
    }
    istringstream parseLine(line);
    string token;
    vector<string> tokens;
    while (getline(parseLine, token, ',')) {
      if (token[0] == ' ') // Remove beginning space.
      {
        token.erase(0, 1);
      }
      tokens.push_back(token);
    }
    string movieType = tokens[0];
    if (movieType == "C") {
      int stock = stoi(tokens[1]);
      string dir = tokens[2];
      string title = tokens[3];
      istringstream ss2(tokens[4]);
      string firstName, lastName, month, year;
      ss2 >> firstName >> lastName >> month >> year;
      inv->addClassicMovie(stock, title, dir, firstName, lastName, stoi(month),
                           stoi(year));
    } else if (movieType == "F" || movieType == "D") {
      int stock = stoi(tokens[1]);
      string dir = tokens[2];
      string title = tokens[3];
      int year = stoi(tokens[4]);
      if (movieType == "F") {
        inv->addComedyMovie(stock, title, dir, year);
      } else {
        inv->addDramaMovie(stock, title, dir, year);
      }
    } else {
      cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
    }
  }
}

void Store::readTransactions(const string &fileName) {
  ifstream in(fileName);
  string line; // Line were reading
  if (!in) {
    cout << "Can't open file " << fileName << endl;
  }
  while (!in.eof()) {
    getline(in, line);
    if (line.empty()) {
      break;
    }
    istringstream parseLine(line);
    string transType;
    parseLine >> transType; // First letter is the Store Transaction Type

    switch (transType[0]) {
    case 'I': {
      displayInventory();
      break;
    }
    case 'H': {
      int custID;
      parseLine >> custID;
      customerDatabase.get(custID)->printHistory();
      break;
    }
    case 'R': {
      int custID;
      string mediaType, movieType;
      parseLine >> custID;
      parseLine >> mediaType;
      if (mediaType == "D") {
        parseLine >> movieType;
        if (movieType == "C") {
          int month, year;
          string first, last;
          // C 5 1940 Katherine Hepburn
          parseLine >> month;
          parseLine >> year;
          parseLine >> first;
          parseLine >> last;
          int idx = inv->getClassicIndex(month, year, first, last);
          if (idx == -1) // If Classic movie doesn't exist, error
          {
            cerr << "ERROR: Classic Movie Not Found!" << endl;
          } else // Otherwise, movie exists
          {
            ClassicMovie *c = inv->peekClassicMovie(idx);
            if (customerDatabase.contains(
                    custID)) // If Customer exists, continue
            {
              // check
              if (customerDatabase.get(custID)->isCurrentlyBorrowing('C',
                                                                     idx)) {
                inv->returnMovie(movieType, idx);
                Transaction *t = new Transaction(
                    'C', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addToHistory(t);
              } else {
                cerr << "ERROR: "
                     << customerDatabase.get(custID)->getFirstName() << " "
                     << customerDatabase.get(custID)->getLastName()
                     << " is not currently borrowing the classic movie "
                     << c->getTitle() << ", " << c->getDirector()
                     << ", so we can't return it." << endl;
              }
            } else // Otherwise, the customer doesn't exist. Throw an error.
            {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "F") {
          // F You've Got Mail, 1998
          int year;
          string title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          title = tokens[0];
          year = stoi(tokens[1]);
          int idx = inv->getComedyIndex(year, title);
          if (idx == -1) {
            cerr << "ERROR: Comedy Movie: " << title << ", " << year
                 << " Not Found!" << endl;
          } else {
            ComedyMovie *c = inv->peekComedyMovie(idx);
            if (customerDatabase.contains(
                    custID)) // if customer exists, continue
            {
              if (customerDatabase.get(custID)->isCurrentlyBorrowing(
                      'F', idx)) // if customer is borrowing this movie, we can
                                 // successfully return it
              {
                inv->returnMovie(movieType, idx);
                Transaction *t = new Transaction(
                    'F', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);

                customerDatabase.get(custID)->addToHistory(t);
              } else {
                cerr << "ERROR: "
                     << customerDatabase.get(custID)->getFirstName() << " "
                     << customerDatabase.get(custID)->getLastName()
                     << " is not currently borrowing the comedy movie "
                     << c->getTitle() << ", " << c->getDirector()
                     << ", so we can't return it." << endl;
              }
            } else // otherwise error for non-existent ID.
            {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "D") {
          // D Barry Levinson, Good Morning Vietnam,
          string director, title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          director = tokens[0];
          title = tokens[1];
          int idx = inv->getDramaIndex(director, title);
          if (idx == -1) // If movie not found throw error
          {
            cerr << "ERROR: Drama Movie: " << title << " by " << director
                 << " Not Found!" << endl;
          } else // Otherwise movie exists, continue
          {
            DramaMovie *d = inv->peekDramaMovie(idx);
            if (customerDatabase.contains(
                    custID)) // if customer exists, continue
            {
              if (customerDatabase.get(custID)->isCurrentlyBorrowing('D',
                                                                     idx)) {
                inv->returnMovie(movieType, idx);
                Transaction *t = new Transaction(
                    'D', d->getTitle(), d->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);

                customerDatabase.get(custID)->addToHistory(t);
              } else {
                cerr << "ERROR: "
                     << customerDatabase.get(custID)->getFirstName() << " "
                     << customerDatabase.get(custID)->getLastName()
                     << " is not currently borrowing the drama movie "
                     << d->getTitle() << ", " << d->getDirector()
                     << ", so we can't return it." << endl;
              }
            } else // throw error for non existing customer
            {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else {
          cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
        }
      } // if media type is d
      else {
        cerr << "ERROR: Invalid Media Type:" << mediaType << endl;
      }
      break;
    }
    case 'B': {
      int custID;
      string movieType, mediaType;
      parseLine >> custID;
      parseLine >> mediaType;
      if (mediaType == "D") {
        parseLine >> movieType;
        if (movieType == "C") {
          int month, year;
          string first, last;
          // C 5 1940 Katherine Hepburn
          parseLine >> month;
          parseLine >> year;
          parseLine >> first;
          parseLine >> last;
          int idx = inv->getClassicIndex(month, year, first, last);
          if (idx == -1) {
            cerr << "ERROR: Classic Movie Not Found!" << endl;
          } else {
            if (customerDatabase.contains(custID)) {
              if (inv->borrowMovie(movieType, idx)) {
                ClassicMovie *c = inv->peekClassicMovie(idx);
                Transaction *t = new Transaction(
                    'C', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addBorrowed('C', idx);
                customerDatabase.get(custID)->addToHistory(t);
              }
            } else {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "F") {
          // F You've Got Mail, 1998
          int year;
          string title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          title = tokens[0];
          year = stoi(tokens[1]);
          int idx = inv->getComedyIndex(year, title);
          if (idx == -1) {
            cerr << "ERROR: Comedy Movie: " << title << ", " << year
                 << " Not Found!" << endl;
          } else {
            if (customerDatabase.contains(custID)) {
              if (inv->borrowMovie(movieType, idx)) {
                ComedyMovie *c = inv->peekComedyMovie(idx);
                Transaction *t = new Transaction(
                    'C', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addBorrowed('F', idx);
                customerDatabase.get(custID)->addToHistory(t);
              }
            } else {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else if (movieType == "D") {
          // D Barry Levinson, Good Morning Vietnam,
          string director, title;
          string token;
          vector<string> tokens;
          while (getline(parseLine, token, ',')) {
            if (token[0] == ' ') // Remove beginning space.
            {
              token.erase(0, 1);
            }
            tokens.push_back(token);
          }
          director = tokens[0];
          title = tokens[1];
          int idx = inv->getDramaIndex(director, title);
          if (idx == -1) {
            cerr << "ERROR: Drama Movie: " << title << " by " << director
                 << " Not Found!" << endl;
          } else {
            if (customerDatabase.contains(custID)) {
              if (inv->borrowMovie(movieType, idx)) {
                DramaMovie *c = inv->peekDramaMovie(idx);
                Transaction *t = new Transaction(
                    'C', c->getTitle(), c->getDirector(),
                    customerDatabase.get(custID)->getFirstName() + " " +
                        customerDatabase.get(custID)->getLastName(),
                    transType[0]);
                customerDatabase.get(custID)->addBorrowed('D', idx);
                customerDatabase.get(custID)->addToHistory(t);
              }
            } else {
              cerr << "ERROR: Invalid Customer ID: " << custID << endl;
            }
          }
        } else {
          cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
        }
      } else {
        cerr << "ERROR: Invalid Media Type:" << mediaType << endl;
      }
      break;
    }
    default:
      cerr << transType << " is an invalid transaction type." << endl;
      break;
    }
    inv->sortMovies();
  }
}

void Store::displayInventory() {
  inv->sortMovies();
  cout << *inv;
}
