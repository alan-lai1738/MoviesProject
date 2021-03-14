#include "Inventory.h"
Inventory::Inventory()
{

}
Inventory::~Inventory()
{
  
}
//Add movie methods
void Inventory::addDramaMovie(int& stock, string& title, string& director, int& releaseYear)
{ 
  auto DramaMovie* d = new DramaMovie(stock, title, director, releaseYear);
  for(auto & i : dramaMovieShelf)
  {
    if(d->equals(dramaMovieShelf[i]))
    {
      dramaMovieShelf[i]->setStock(d->getStockAmt()+dramaMovieShelf[i]->getStockAmt());
      return;
    }
  }
  dramaMovieShelf.push_back(d);
}

void Inventory::addComedyMovie(int& stock, string& title, string& director, int& releaseYear)
{
  auto ComedyMovie* f = new ComedyMovie(stock, title, director, releaseYear);
  for(auto & i : comedyMovieShelf)
  {
    if(f->equals(comedyMovieShelf[i]))
    {
      comedyMovieShelf[i]->setStock(f->getStockAmt()+comedyMovieShelf[i]->getStockAmt());
      return;
    }
  }
  comedyMovieShelf.push_back(f);
}

void Inventory::addClassicMovie(int& stock, string& title, string& director, string& majActorFirstName, string& majActorLastName, int& relMonth, int& relYear)
{
  ClassicMovie* c = new ClassicMovie(stock, title, director, majActorFirstName, majActorLastName, relMonth, relYear);
  for(int i = 0; i < classicMovieShelf.size(); i++)
  {
    if(c->equals(classicMovieShelf[i]))
    {
      classicMovieShelf[i]->setStock(c->getStockAmt()+classicMovieShelf[i]->getStockAmt());
      return;
    }
  }
  classicMovieShelf.push_back(c);
}

//Getters
ClassicMovie* Inventory::peekClassicMovie(int& index) const
{
  if(index >= classicMovieShelf.size() || index < 0)
  {
    cerr << "ERROR: Index exceeds ClassicMovieShelf size" << endl;
    return nullptr;
  }
  return classicMovieShelf[index];
}

ComedyMovie* Inventory::peekComedyMovie(int& index) const
{
  if(index >= comedyMovieShelf.size() || index < 0)
  {
    cerr << "ERROR: Index exceeds ComedyMovieShelf size" << endl;
    return nullptr;
  }
  return comedyMovieShelf[index];
}

DramaMovie* Inventory::peekDramaMovie(int& index) const
{
  if(index >= dramaMovieShelf.size() || index < 0)
  {
    cerr << "ERROR: Index exceeds DramaMovieShelf size" << endl;
    return nullptr;
  }
  return dramaMovieShelf[index];
}

int Inventory::getClassicIndex(int& month, int& year, string& first, string& last)
{
  for(int i = 0; i < classicMovieShelf.size(); i++)
  {
    if(classicMovieShelf[i]->getReleaseMonth() == month
    && classicMovieShelf[i]->getReleaseYear() == year
    && classicMovieShelf[i]->getMajorActorFirst() == first
    && classicMovieShelf[i]->getMajorActorLast() == last)
    {
      return i;
    }
  }
  return -1;
}

int Inventory::getComedyIndex(int& year, string& title)
{
  for(int i = 0; i < comedyMovieShelf.size(); i++)
  {
    if(comedyMovieShelf[i]->getReleaseYear() == year && comedyMovieShelf[i]->getTitle() == title)
    {
      return i;
    }
  }
  return -1;
}

int Inventory::getDramaIndex(string& director, string& title)
{
  for(int i = 0; i < dramaMovieShelf.size(); i++)
  {
    if(dramaMovieShelf[i]->getDirector() == director && dramaMovieShelf[i]->getTitle() == title)
    {
      return i;
    }
  }
  return -1;
}

bool Inventory::borrowMovie(string& movie_type, int& index)
{
  if(movie_type == "C")
  {
    int stockAmt = classicMovieShelf[index]->getStockAmt();
    if(stockAmt >= 1)
    {
      classicMovieShelf[index]->setStock(classicMovieShelf[index]->getStockAmt()-1);
      classicMovieShelf[index]->setBorrowed(classicMovieShelf[index]->getBorrowedAmt()+1);
      return true;
    }
    else
    {
      cerr << "ERROR: Insufficient stock of " << classicMovieShelf[index]->getTitle() << ", " << classicMovieShelf[index]->getReleaseMonth() << " " << classicMovieShelf[index]->getReleaseYear() << endl;
      return false;
    }
  }
  else if(movie_type == "F")
  {
    int stockAmt = comedyMovieShelf[index]->getStockAmt();
    if(stockAmt >= 1)
    {
      comedyMovieShelf[index]->setStock(comedyMovieShelf[index]->getStockAmt()-1);
      comedyMovieShelf[index]->setBorrowed(comedyMovieShelf[index]->getBorrowedAmt()+1);
      return true;
    }
    else
    {
      cerr << "ERROR: Insufficient stock of " << comedyMovieShelf[index]->getTitle() << ", " << comedyMovieShelf[index]->getReleaseYear() << endl;
      return false;
    }
  }
  else if(movie_type == "D")
  {
    int stockAmt = dramaMovieShelf[index]->getStockAmt();
    if(stockAmt >= 1)
    {
      dramaMovieShelf[index]->setStock(dramaMovieShelf[index]->getStockAmt()-1);
      dramaMovieShelf[index]->setBorrowed(dramaMovieShelf[index]->getBorrowedAmt()+1);
      return true;
    }
    else
    {
      cerr << "ERROR: Insufficient stock of " << dramaMovieShelf[index]->getTitle() << ", " << dramaMovieShelf[index]->getReleaseYear() << endl;
      return false;
    }
  }
  return false;
}

void Inventory::returnMovie(string& movie_type, int& index)
{
  if(movie_type == "C")
  {
    classicMovieShelf[index]->setStock(classicMovieShelf[index]->getStockAmt()+1);
    classicMovieShelf[index]->setBorrowed(classicMovieShelf[index]->getBorrowedAmt()-1);
  }
  if(movie_type == "F")
  {
    comedyMovieShelf[index]->setStock(comedyMovieShelf[index]->getStockAmt()+1);
    comedyMovieShelf[index]->setBorrowed(comedyMovieShelf[index]->getBorrowedAmt()-1);
  }
  if(movie_type == "D")
  {
    dramaMovieShelf[index]->setStock(dramaMovieShelf[index]->getStockAmt()+1);
    dramaMovieShelf[index]->setBorrowed(dramaMovieShelf[index]->getBorrowedAmt()-1);
  }
}


bool Inventory::sortByDrama(DramaMovie* a, DramaMovie* b)
{
  return a->lessThan(b);
}

bool Inventory::sortByComedy(ComedyMovie* a, ComedyMovie* b)
{
  return a->lessThan(b);
}

bool Inventory::sortByClassic(ClassicMovie* a, ClassicMovie* b)
{
  return a->lessThan(b);
}

void Inventory::sortMovies()
{
  std::sort(classicMovieShelf.begin(), classicMovieShelf.end(), sortByClassic);
  std::sort(comedyMovieShelf.begin(), comedyMovieShelf.end(), sortByComedy);
  std::sort(dramaMovieShelf.begin(), dramaMovieShelf.end(), sortByDrama);

}

