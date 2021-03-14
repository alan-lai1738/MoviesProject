#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include <iostream>
using namespace std;
class Transaction
{
  friend ostream& operator<<(ostream& os, const Transaction &rhs)
  {
    os << rhs.customerInvolved << " " << rhs.transactionType << "ed " << "'" << rhs.movieTitle << "' which is a " << rhs.movieType << " movie by " << rhs.director << endl;
    return os;
  }

  public:
    Transaction(char movType, string movTitle, string dirName, string customerName, char type);
    ~Transaction();
    private:
      string movieType;
      string movieTitle;
      string director;

      string customerInvolved;
      string transactionType;
};

#endif
