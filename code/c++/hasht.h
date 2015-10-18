/*
 * File:   hasht.h
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 21:44
 */
#include <iostream>
#include <vector>

#ifndef HASHT_H
#define	HASHT_H
struct document{
   int id;
   std::string name;
   int frequency;
};
struct token{
   token* prev;
   std::string name;
   std::vector<document> docs;
   token* next;
};

class hasht{
private:
   static const int tableSize = 4;
   token* HashTable[tableSize];
public:
    hasht();
    int hash(std::string key);
    bool addToken(std::string name, document doc);
    bool addDocument(std::string tokenName, document doc);
    int numberOftokensInIndex(int index);
    document* findDocument(int id, std::string token);
    token* findToken(std::string name);
    bool removeToken(std::string name);
};

#endif	/* HASHT_H */
