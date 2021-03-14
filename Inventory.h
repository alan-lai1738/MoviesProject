#ifndef INVENTORY_H
#define INVENTORY_H
#include "Movie.h"
#include "DramaMovie.h"
#include "ClassicMovie.h"
#include "ComedyMovie.h"
#include<algorithm>
#include <string>
#include <vector>

//friend class Store;
class Inventory
{
  friend ostream& operator<<(ostream& os, const Inventory& inv)
  {
    os << "____________________[Viewing Inventory]____________________" << endl;
    for(int i = 0; i < inv.comedyMovieShelf.size(); i++)
    {
      os << *(inv.comedyMovieShelf[i]);
    }
    for(int j = 0; j < inv.dramaMovieShelf.size(); j++)
    {
       os << *(inv.dramaMovieShelf[j]);
    }
    for(int k = 0; k < inv.classicMovieShelf.size(); k++)
    {
       os << *(inv.classicMovieShelf[k]);
    }
    return os;
  }
  public:
    Inventory();
    ~Inventory();
    
    void addClassicMovie(int stock, string title, string director, string majActorFirstName, string majActorLastName, int relMonth, int relYear);
    
    void addComedyMovie(int stock, string title, string director, int releaseYear);

    void addDramaMovie(int stock, string title, string director, int releaseYear);

    bool borrowMovie(string movie_type, int index);
    void returnMovie(string movie_type, int index);

    ClassicMovie* peekClassicMovie(int index) const;
    ComedyMovie* peekComedyMovie(int index) const;
    DramaMovie* peekDramaMovie(int index) const;
    int getClassicIndex(int month, int year, string first, string last);
    int getComedyIndex(int year, string title);
    int getDramaIndex(string director, string title);
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