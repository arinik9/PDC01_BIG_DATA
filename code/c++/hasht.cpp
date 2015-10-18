#include <iostream>
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
bool hasht::addToken(string name, document* doc){
    token* existingToken = findToken(name);
    if (existingToken != NULL) {
        //Token already exists
        return false;
    }
    int index = hash(name);
    if(HashTable[index] == NULL){
        HashTable[index] = new token;
        HashTable[index]->name = name;
        HashTable[index]->doc = doc;
        HashTable[index]->next = NULL;
        HashTable[index]->prev = NULL;
    }
    else{
        token* ptr = HashTable[index];
        token* n = new token;
        n->name = name;
        n->doc = doc;
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
bool hasht::addDocument(string tokenName, document* doc){
    token* existingToken = findToken(tokenName);
    if (existingToken == NULL) {
        //Token does not exist
        return false;
    }
    if (findDocument(doc->id, tokenName) != NULL){
        return false;
    }
    document* iter = existingToken->doc;
    while (iter->next != NULL){
        iter=iter->next;
    }
    iter->next=doc;

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
    document* doc = ptr->doc;
    while (doc != NULL){
        if(doc->id == id){
            //document exists in specified token
            return doc;
        }
        doc = doc->next;
    }
    //token exists but not in specified document
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
