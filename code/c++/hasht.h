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
   document * next;
   int frequency;
};
struct token{
   int index;
   std::string name;
   document * doc;
};
struct hashToken{
   hashToken* prev;
   hashToken* next;
   token* t;

};

class hasht{
private:
   static const int tableSize = 500;
   int count;
   hashToken* HashTable[tableSize];
public:
    hasht();
    int hash(std::string key);
    bool addToken(std::string name);
    bool addDocument(std::string tokenName, document* doc);
    int numberOftokensInIndex(int index);
    document* findDocument(int id, std::string token);
    token* findToken(std::string name);
    hashToken* findParentToken(std::string name);
    bool removeToken(std::string name);
    void displayHashTable();
    bool initializeHashTable();
};

#endif	/* HASHT_H */
