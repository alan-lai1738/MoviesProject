#include "Customer.h"

Customer::Customer(string& first, string& last, int& id)
{
  customerFirstName = first;
  customerSecondName = last;
  customerID = id;
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
  if(history.empty())
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

void Customer::addBorrowed(char movieType, int movieIndex)
{
  borrowedMovies.emplace_back(make_pair(movieType, movieIndex));
}

void Customer::returnADVD(char movieType, int movieIndex)
{
  for(int i = 0; i < borrowedMovies.size(); i++)
  {
    if(borrowedMovies[i].first == movieType && borrowedMovies[i].second == movieIndex)
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
  return count(borrowedMovies.begin(), borrowedMovies.end(), make_pair(movieType, movieIndex)!=0);
}