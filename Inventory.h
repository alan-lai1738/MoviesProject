#ifndef INVENTORY_H
#define INVENTORY_H
#include "ClassicMovie.h"
#include "ComedyMovie.h"
#include "DramaMovie.h"
#include "Movie.h"
#include <algorithm>
#include <string>
#include <vector>

//friend class Store;
class Inventory
{
  friend ostream& operator<<(ostream& os, const Inventory& inv)
  {
    os << "____________________[Viewing Inventory]____________________" << endl;
    for(auto i : inv.comedyMovieShelf)
    {
      os << *(i);
    }
    for(auto j : inv.dramaMovieShelf)
    {
       os << *(j);
    }
    for(auto k : inv.classicMovieShelf)
    {
       os << *(k);
    }
    return os;
  }
  public:
    Inventory();
    ~Inventory();
    
    void addClassicMovie(const int& stock, const string& title, const string& director, const string& majActorFirstName, const string& majActorLastName, const int& relMonth, const int& relYear);
    
    void addComedyMovie(const int& stock, const string& title, const string& director, const int& releaseYear);

    void addDramaMovie(const int& stock, const string& title, const string& director, const int& releaseYear);

    bool borrowMovie(const string& movieType, const int& index);
    void returnMovie(const string& movieType, const int& index);

    ClassicMovie* peekClassicMovie(const int& index) const;
    ComedyMovie* peekComedyMovie(const int& index) const;
    DramaMovie* peekDramaMovie(const int& index) const;
    int getClassicIndex(const int& month, const int& year, const string& first, const string& last);
    int getComedyIndex(const int& year, const string& title);
    int getDramaIndex(const string& director, const string& title);
    void sortMovies();
  private:
    vector<ClassicMovie*> classicMovieShelf;
    vector<ComedyMovie*> comedyMovieShelf;
    vector<DramaMovie*> dramaMovieShelf;

    static bool sortByDrama(DramaMovie* a, DramaMovie* b);
    static bool sortByComedy(ComedyMovie* a, ComedyMovie* b);
    static bool sortByClassic(ClassicMovie* a, ClassicMovie* b);

 

};
#endif