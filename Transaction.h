#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <iostream>
#include <string>
using namespace std;
class Transaction {
  friend ostream &operator<<(ostream &os, const Transaction &rhs) {
    os << rhs.customerInvolved << " " << rhs.transactionType << "ed "
       << "'" << rhs.movieTitle << "' which is a " << rhs.movieType
       << " movie by " << rhs.director << endl;
    return os;
  }

public:
  Transaction(const char &movType, const string &movTitle,
              const string &dirName, const string &customerName,
              const char &type);

private:
  string movieType;
  string movieTitle;
  string director;

  string customerInvolved;
  string transactionType;
};

#endif
