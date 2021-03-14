#ifndef STORE_H
#define STORE_H
#include "Customer.h"
#include "HashTable.h"
#include "Inventory.h"
#include "Movie.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Store {
public:
  Store();
  string getHistory(const int &id) const;
  void stockDVDShelves(const string &fileName);
  void fillCustomerDatabase(const string &fileName);
  void readTransactions(const string &fileName);
  void displayInventory();

private:
  HashTable<int, Customer *> customerDatabase;
  Inventory *inv;
};
#endif