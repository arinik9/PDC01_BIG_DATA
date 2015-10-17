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
   document * doc;
   token* next;
};

class hasht{
private:
   static const int tableSize = 4;
   token* HashTable[tableSize];
public:
    hasht();
    int Hash(std::string key);
    bool AddToken(std::string name, document* doc);
    bool AddDocument(std::string tokenName, document* doc);
    int NumberOftokensInIndex(int index);
    document* FindDocument(int id, std::string token);
    token* FindToken(std::string name);
    bool RemoveToken(std::string name);
};

#endif	/* HASHT_H */
