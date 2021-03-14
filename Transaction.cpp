#include "Transaction.h"
#include "Movie.h"

Transaction::Transaction(char movType, string movTitle, string dirName, string customerName, char type)
{
  switch(movType)
  {
    case 'F' : 
      movieType = "Comedy";
      break;
    case 'C' :
      movieType = "Classic";
      break;
    case 'D' :
      movieType = "Drama";
      break;
  }
  movieTitle = movTitle;
  director = dirName;
  customerInvolved = customerName;
  if(type == 'B')
  {
    transactionType = "borrow";
  }
  else if(type == 'R')
  {
    transactionType = "return";
  }
}

Transaction::~Transaction()
{
  
}