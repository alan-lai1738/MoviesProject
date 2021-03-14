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

class ComedyMovie : public Movie {
public:
  ComedyMovie(const int &stock, const string &title, const string &director,
              const int &releaseYear)
      : Movie(stock, title, director, releaseYear) {
    this->type = 'F';
  }
  ostream &display(ostream &os) const override {
    os << "[" << title << "] Comedy | " << releaseYear << " | By " << director
       << " | " << stock << " copies available / " << borrowed
       << " copies currently being borrowed." << endl;
    return os;
  }

  bool equals(Movie *m) const override {
    return ((type == m->getType()) && (title == m->getTitle()) &&
            (director == m->getDirector()) &&
            (releaseYear == m->getReleaseYear()));
  }

  bool greaterThan(Movie *m) const override { return (!lessThan(m)); }

  bool lessThan(Movie *m) const override {
    if (equals(m)) {
      return false;
    }
    if (title != m->getTitle()) {
      return title < m->getTitle();
    }
    if (releaseYear != m->getReleaseYear()) {
      return releaseYear < m->getReleaseYear();
    }
    return false;
  }
};
#endif