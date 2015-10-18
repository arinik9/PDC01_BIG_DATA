#include <iostream>
#include <fstream>
#include <vector>
#include "hasht.h"

using namespace std;
hasht::hasht(){
    for(int i = 0; i < tableSize; i++)
    {
        HashTable[i] = NULL;
    }
}
int hasht::hash(string key){
    int index;
    unsigned int hash=0;
    for(int i = 0; i<key.length();i++){
        hash =(hash + (int)key[i])*17;
    }
    index = hash % tableSize;
    if (index < 0){
        index += tableSize;
    }
    return index;
}
bool hasht::addToken(string name, document doc){
    token* existingToken = findToken(name);
    if (existingToken != NULL) {
        //Token already exists
        return false;
    }
    int index = hash(name);
    if(HashTable[index] == NULL){
        HashTable[index] = new token;
        HashTable[index]->name = name;
        HashTable[index]->docs.push_back(doc);
        HashTable[index]->next = NULL;
        HashTable[index]->prev = NULL;
    }
    else{
        token* ptr = HashTable[index];
        token* n = new token;
        n->name = name;
        n->docs.push_back(doc);
        n->next = NULL;
        n->prev = NULL;
        while(ptr->next != NULL){
            ptr = ptr->next;
        }
        ptr->next = n;
        n->prev = ptr;
    }
    return true;
}
bool hasht::addDocument(string tokenName, document doc){
    token* existingToken = findToken(tokenName);
    if (existingToken == NULL) {
        //Token does not exist
        return false;
    }
    if (findDocument(doc.id, tokenName) != NULL){
        return false;
    }
    existingToken->docs.push_back(doc);

}
int hasht::numberOftokensInIndex(int index){
    int count = 0;
    if(HashTable[index] == NULL){
        return count;
    }
    count++;
    token* iter=HashTable[index];
    while(iter->next != NULL){
        count++;
        iter = iter->next;
    }
    return count;
}
token* hasht::findToken(string name){
    int index = hash(name);
    token* iter = HashTable[index];
    while (iter != NULL){
        if (iter->name == name){
            break;
        }
        iter = iter->next;
    }
    return iter;
}
document* hasht::findDocument(int id, string myToken){
    token* ptr = findToken(myToken);
    if (ptr == NULL){
        //token does not exist in table
        return NULL;
    }
    for(vector<document>::iterator it = ptr->docs.begin();
            it != ptr->docs.end(); it++){
        if (it->id == id){
            return &(*it);
        }
    }
    return NULL;
}
bool hasht::removeToken(string name){
    token* delPtr = findToken(name);
    token* p1;
    token* p2;
    if (delPtr == NULL){
        return false;
    }
    if (delPtr->prev == NULL){
        //worst case scenario, we need to get hash again
        int index = hash(name);
        HashTable[index] = delPtr->next;
        delete delPtr;
        return true;
    }
    delPtr->prev->next = delPtr->next;
    delete delPtr;
    return true;
}

bool hasht::saveOnFile(std::string path)
{
    ofstream ofs(path.c_str(),ios::binary);
    
    if(!ofs.is_open())return false;

    int sizeTable = this->tableSize;

    //write table size
    ofs.write((const char *)&sizeTable,sizeof(sizeTable));

    for (int i = 0; i < sizeTable; i++)
    {
        if(HashTable[i] != NULL)
        {
            //write index
            ofs.write((const char *)&i,sizeof(i));
            
            //write nb of tokens
            int nbToken = 0;
            token* iter = HashTable[i];
            while(iter != NULL){
               nbToken++;
            }
            ofs.write((const char *)&nbToken,sizeof(nbToken));

            //write tokens
            iter = HashTable[i];        
            while(iter != NULL){
                ofs.write((const char *)iter,sizeof(iter));
                iter = iter->next;
            }
        }
    }
}
