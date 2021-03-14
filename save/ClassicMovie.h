#ifndef CLASSICMOVIE_H
#define CLASSICMOVIE_H
#include "Movie.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


class ClassicMovie: public Movie {
  public:
    // Default constructor
    explicit ClassicMovie(int& stock, string& title, string& director, string& majActorFirstName, string& majActorLastName, int& relMonth, int& relYear)
    {
      this->stock = stock;
      this->title = title;
      this->director = director;
      this->releaseYear = relYear;
      this->majorActorFirst = majActorFirstName;
      this->majorActorLast = majActorLastName;
      this->releaseMonth = relMonth;
      this->type = 'C';
    }
    //Getters
    int getReleaseMonth() const
    {
      return releaseMonth;
    }
    string getMajorActorFirst() const
    {
      return majorActorFirst;
    }
    string getMajorActorLast() const
    {
      return majorActorLast;
    }

    ostream &display(ostream &os) const override
    {
      os << "[" << title << "] Classic | " << releaseMonth << "/" << releaseYear << " | By " << director << " | " << "Featuring " << majorActorFirst << " " << majorActorLast
      << " | " << stock << " copies available / " << borrowed << " copies currently being borrowed." << endl;
      return os;
    }
    
    bool equals(Movie* other) const override
    {
      assert(other != nullptr);
      auto ClassicMovie* otherMovie = dynamic_cast<ClassicMovie*>(other);
      //assert(otherMovie && otherMovie == other);
      return(
      title == otherMovie->title &&
      director == otherMovie->director &&
      releaseMonth == otherMovie->releaseMonth &&
      releaseYear == otherMovie->releaseYear &&
      majorActorFirst == otherMovie->majorActorFirst &&
      majorActorLast == otherMovie->majorActorLast
      );
    }


    bool greaterThan(Movie* other) const override
    {
      if(equals(other))
      {
        return false;
      }
      return (!lessThan(other));
    }

    
    bool lessThan(Movie* other) const override
    {
      assert(other != nullptr);
      ClassicMovie  m = dynamic_cast<ClassicMovie*>(other);
      if(equals(other))
      {
        return false;
      }
      if(m.getReleaseYear() > releaseYear)
      {
        return true;
      }
      if(m.getReleaseYear() == releaseYear)
      {
        if(m.getReleaseMonth() > releaseMonth)
        {
          return true;
        }
        else if(m.getReleaseMonth() == releaseMonth)
        {
          if(m.getMajorActorFirst() > majorActorFirst)
          {
            return true;
          }
          else if(m.getMajorActorFirst() == majorActorFirst)
          {
            if(m.getMajorActorLast() > majorActorLast)
            {
              return true;
            }
            else
            {
              return false;
            }
          }
        }
      }
      return false;
    }
  
  private:
    string majorActorFirst;
    string majorActorLast;
    int releaseMonth;
    
};
#endif