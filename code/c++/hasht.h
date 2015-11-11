/*
 * File:   hasht.h
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 21:44
 */
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

#ifndef HASHT_H
#define	HASHT_H

class hasht{
private:
   static const int tableSize = 500;
   int count;
   int nb_tokens;
   hashToken* HashTable[tableSize];
   std::ifstream fromFile;
   std::ofstream toFile;
   std::string filename; //for re-launching the system
public:
    hasht(std::string name);
    hasht(const hasht & h);
    int hash(std::string key);
    bool addToken(std::string name, int id, unsigned int nbDoc=0, unsigned int offset=0);
    bool addDocument(std::string tokenName, document* doc);
    int numberOftokensInIndex(int index);
    document* findDocument(int id, std::string token);
    token* findToken(std::string name);
    hashToken* findParentToken(std::string name);
    void displayHashTable();
    void writeAllTokensToFile(double* normsOfDocs, int nbFiles);
    double* readAllTokensFromFile();
};

#endif	/* HASHT_H */

