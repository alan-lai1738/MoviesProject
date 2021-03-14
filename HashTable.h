#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
template<typename K, typename V>
class HashTable{
  friend ostream& operator<<(ostream& os, const HashTable &h)
  {
    for(int i = 0; i < h.keys.size(); i++)
    {
      os << "[" << h.keys[i] << "]: " << h.values[i] << endl;
    }
    return os;
  }
  public:
    HashTable()
    {
    }
    ~HashTable()
    {
    }
    
    void put(K& key, V& value)
    {
      if(find(keys.begin(), keys.end(), key) != keys.end()) // If our hashtable contains the key
      {
        int index = getIndex(key);  // We get the key's index, and update the value for that key.
        values[index] = value;
      }
      else
      {
        keys.push_back(key);
        values.push_back(value);
      }
    }
    
    void remove(K key)
    {
      if(!find(keys.begin(), keys.end(), key) != keys.end())
      {
        return;
      }
      int index = getIndex(key);
      keys.erase(keys.begin()+index);
      values.erase(values.begin()+index);
    }

bool contains(K key)
{
  return find(keys.begin(), keys.end(), key) != keys.end();
}

V& get(K key)
{
  int index = getIndex(key);
  return values[index];
}

bool empty()
{
  return (keys.size() == 0);
}

int size()
{
  return keys.size();
}
    
    private:
      vector<K> keys;
      vector<V> values;
      int getIndex(K key)
      {
        auto it = find(keys.begin(), keys.end(), key);
        if(it != keys.end())
        {
          int index = it-keys.begin();
          return index;
        }
        return -1;
      }
};
#endif

