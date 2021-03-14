#ifndef DRAMAMOVIE_H
#define DRAMAMOVIE_H
#include "Movie.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


class DramaMovie: public Movie {
  public:
    DramaMovie(int& stock, string& title, string& director, int& releaseYear)
    {
      this->stock = stock;
      this->title = title;
      this->director = director;
      this->releaseYear = releaseYear;
      this->type = 'D';
    }
    
    ostream &display(ostream &os) const override
    {
      os << "[" << title << "] Drama | " << releaseYear << " | By " << director << " | " << stock << " copies available / " << borrowed << " copies currently being borrowed." << endl;
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
      if(m->getDirector() > director)
      {
        return true;
      }
      if(m->getDirector() == director)
      {
        if(m->getTitle() > title)
        {
          return true;
        }
      }
      return false;
    }
};
#endif


   