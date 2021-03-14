#include "Customer.h"

Customer::Customer(string first, string last, int ID)
{
  customerFirstName = first;
  customerSecondName = last;
  customerID = ID;
}
Customer::~Customer()
{
  
}
void Customer::addToHistory(Transaction* t)
{
  history.push_back(t);
}

string Customer::getFirstName() const
{
  return customerFirstName;
}

string Customer::getLastName() const
{
  return customerSecondName;
}

int Customer::getCustomerID() const
{
  return customerID;
}

void Customer::printHistory()
{
  
  cout << "____________________[Displaying " << customerFirstName << " " << customerSecondName << "'s History]____________________" << endl;
  if(history.size() == 0)
  {
    cout << "History is Empty!" << endl;
  }
  else 
  {
    for(int i = history.size()-1; i > 0; i--)
    {
      cout <<  *history[i] << endl;
    }
  }
}

void Customer::addBorrowed(char c, int i)
{
  borrowedMovies.push_back(make_pair(c, i));
}

void Customer::returnADVD(char c, int movieIndex)
{
  for(int i = 0; i < borrowedMovies.size(); i++)
  {
    if(borrowedMovies[i].first == c && borrowedMovies[i].second == movieIndex)
    {
      borrowedMovies.erase(borrowedMovies.begin()+i);
      return;
    }
  }
  //cerr << "SOMEHOW A MOVIE DIDNT GET RETURNED...PLEASE DO PROPER CHECKS IN STORE .CPP BEFORE RUNNING THIS METHOD" << endl;
}


bool Customer::isCurrentlyBorrowing(char movieType, int movieIndex)
{
  /*for(int i = 0; i < borrowedMovies.size(); i++)
  {
    if(borrowedMovies[i].first == movieType && borrowedMovies[i].second == movieIndex)
    {

    }
  }*/
  return count(borrowedMovies.begin(), borrowedMovies.end(), make_pair(movieType, movieIndex));
}