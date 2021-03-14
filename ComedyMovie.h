#ifndef COMEDYMOVIE_H
#define COMEDYMOVIE_H
#include "Movie.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;


class ComedyMovie: public Movie {
  public:
    ComedyMovie(const int& stock, const string& title, const string& director, const int& releaseYear)
    {
      this->stock = stock;
      this->title = title;
      this->director = director;
      this->releaseYear = releaseYear;
      this->type = 'F';
    }
    ostream &display(ostream &os) const override
    {
      os << "[" << title << "] Comedy | " << releaseYear << " | By " << director << " | " << stock << " copies available / " << borrowed << " copies currently being borrowed." << endl;
      return os;
    }
    
    bool equals(Movie* m) const override
    {
      return (
      (type == m->getType()) &&
      (title == m->getTitle()) &&
      (director == m->getDirector()) &&
      (releaseYear == m->getReleaseYear()));
    }
  
    bool greaterThan(Movie* m) const override
    {
      return (!lessThan(m));
    }

    bool lessThan(Movie* m) const override
    {
      if(equals(m))
      {
        return false;
      }
      if(m->getTitle() > title)
      {
        return true;
      }
      if(m->getTitle() == title)
      {
        if(m->getReleaseYear() > releaseYear)
        {
          return true;
        }
      }
      return false;
    }
   
};
#endif