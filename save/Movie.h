#ifndef MOVIE_H
#define MOVIE_H


#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Movie
{
  // To be overloaded in subclass: Classic/Drama/Comedy may have different outputs depending on data values
  friend ostream &operator<<(ostream& os, const Movie &rhs)
  {
    return rhs.display(os);
  }

 protected:
      int stock;        
      string director;  
      string title;
      int releaseYear;
      char type;
      int borrowed = 0;

      virtual ostream &display(ostream &os) const = 0;
     // virtual bool operator==(const Movie&) const = 0;
            
      //virtual void set(Movie* m);
      virtual bool equals(Movie* m) const = 0;
      virtual bool lessThan(Movie* m) const = 0;
      virtual bool greaterThan(Movie* m) const = 0;
      
  public:
    // Setters and getters for values
    string getDirector() const
    {
      return director;
    }
    
    string getTitle() const
    {
      return title;
    }
    
    int getReleaseYear() const
    {
      return releaseYear;
    }

    int getStockAmt() const
    {
      return stock;
    }

    char getType() const
    {
      return type;
    }
    
    void setStock(int amt)
    {
      this->stock = amt;
    }      

    void setBorrowed(int amt)
    {
      borrowed = amt;
    }

    int getBorrowedAmt() const
    {
      return borrowed;
    }
};

#endif