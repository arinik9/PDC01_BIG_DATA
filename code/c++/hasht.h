/*
 * File:   hasht.h
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 21:44
 */
#include <iostream>

#ifndef HASHT_H
#define	HASHT_H
struct document{
   int id;
   std::string name;
   document * next;
   int frequency;
};
struct token{
   token* prev;
   std::string name;
   int index;
   document * doc;
   token* next;
};

class hasht{
private:
   static const int tableSize = 500;
   token* HashTable[tableSize];
public:
    hasht();
    int hash(std::string key);
    bool addToken(std::string name, document* doc);
    bool addDocument(std::string tokenName, document* doc);
    int numberOftokensInIndex(int index);
    document* findDocument(int id, std::string token);
    token* findToken(std::string name);
    bool removeToken(std::string name);
    void displayHashTable();
    bool initializeHashTable();
};

#endif	/* HASHT_H */
