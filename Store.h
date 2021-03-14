#ifndef STORE_H
#define STORE_H
#include "HashTable.h"
#include "Movie.h"
#include "Customer.h"
#include "Inventory.h"
#include <string>
using namespace std;

class Store{
  public:
    Store();
    string getHistory(int ID) const;
    void stockDVDShelves(string fileName);
    void fillCustomerDatabase(string fileName);
    void readTransactions(string fileName);
    void displayInventory();
  private:
    HashTable<int, Customer*> customerDatabase;
    Inventory* inv;
};
#endif