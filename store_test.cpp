/**
 * Testing ass4 movie store functions
 *
 * @author Yusuf Pisan
 * @date 19 Jan 2019
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void testStore1() {
  cout << "Start testStore1" << endl;
  // Should do something more, but lets just read files
  // since each implementation will
  string cfile = "testcommands-1.txt";
  stringstream out;
  ifstream fs(cfile);
  assert(fs.is_open());
  char commandType;
  string discard;
  while (fs >> commandType) {
    out << commandType;
    getline(fs, discard);
  }
  fs.close();
  string result = "IHHBRIBBIH";
  assert(out.str() == result);
  cout << "End testStore1" << endl;
}

void testStore2() {
  cout << "Start testStore2" << endl;
  cout << "End testStore2" << endl;
}

void testStoreFinal() {
  cout << "=====================================" << endl;
  cout << "Start testStoreFinal" << endl;
  cout << "End testStoreFinal" << endl;
  cout << "=====================================" << endl;
}

void testMovies()
{
  cout << "Running movie tests" << endl;
  ClassicMovie c(5, "ClassicMovie Title", "Rin Shima", "Rin", "Shima", 5, 2000);
  assert(c.getStockAmt() == 5);
  assert(c.getDirector() == "Rin Shima");
  assert(c.getMajorActorFirst() == "Rin");
  assert(c.getMajorActorFirst() == "Shima");
  ClassicMovie c2(15, "Another Classic", "Rin Shima", "Rin", "Shima", 5, 1995);
  assert(c.greaterThan(c2) == true);
  assert(c.lessThan(c2) == true);
  

}

void testHashmap()
{

}

void testCustomerAndTransactions()
{

}

void testStoreAndInventory()
{

}

void testAll() {
  testStore1();
  testStore2();
  testStoreFinal();
  testMovies();
}
