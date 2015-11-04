/*
 * File:   hasht.h
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 21:44
 */
#include <iostream>

#ifndef HASHT_H
#define	HASHT_H

class hasht{
private:
   static const int tableSize = 500;
   int count;
   int nb_tokens;
   hashToken* HashTable[tableSize];
public:
    hasht();
    int hash(std::string key);
    bool addToken(std::string name, int id);
    bool addDocument(std::string tokenName, document* doc);
    int numberOftokensInIndex(int index);
    document* findDocument(int id, std::string token);
    token* findToken(std::string name);
    hashToken* findParentToken(std::string name);
    void displayHashTable();
};

#endif	/* HASHT_H */
