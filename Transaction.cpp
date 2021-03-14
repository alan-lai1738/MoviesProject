#include "Transaction.h"
#include "Movie.h"

Transaction::Transaction(const char &movType, const string &movTitle,
                         const string &dirName, const string &customerName,
                         const char &type) {
  switch (movType) {
  case 'F':
    movieType = "Comedy";
    break;
  case 'C':
    movieType = "Classic";
    break;
  case 'D':
    movieType = "Drama";
    break;
  default:
    cerr << "ERROR: Invalid Movie Type: " << movieType << endl;
    break;
  }
  movieTitle = movTitle;
  director = dirName;
  customerInvolved = customerName;
  if (type == 'B') {
    transactionType = "borrow";
  } else if (type == 'R') {
    transactionType = "return";
  }
}
