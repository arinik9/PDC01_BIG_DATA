/* 
 * File:   hasht.h
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 21:44
 */
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
#ifndef HASHT_H
#define	HASHT_H

class hasht{
private:
   static const int tableSize = 4;
   struct item{
       string name;
       string drink;
       item* next;
   };
   item* HashTable[tableSize];
public:
    hasht();
    int Hash(string key);
    void AddItem(string name, string drink);
    int NumberOfItemsInIdex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    void FindDrink(string name);
    void RemoveItem(string name);
        
};
    
#endif	/* HASHT_H */

