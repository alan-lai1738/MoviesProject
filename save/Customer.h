#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Transaction.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Customer
{
  friend ostream& operator<<(ostream& os, const Customer &c)
  {
    os << c.customerFirstName << " " << c.customerSecondName << endl;
    return os;
  }
  public:
    Customer(string& first, string& last, int& id);
    ~Customer();
    void addToHistory(Transaction* t);
    string getFirstName() const;
    string getLastName() const;
    int getCustomerID() const;
    void printHistory();
    void addBorrowed(char movieType, int movieIndex);
    void returnADVD(char movieType, int movieIndex);
    bool isCurrentlyBorrowing(char movieType, int movieIndex);
  private:
    int customerID;
    string customerFirstName;
    string customerSecondName;
    vector<Transaction*> history;
    vector<pair<char, int>> borrowedMovies;
};
#endif