#include <iostream>
#include "dataStructure.h"
#include "hasht.h"

using namespace std;
hasht::hasht(){
    for(int i = 0; i < tableSize; i++)
    {
        HashTable[i] = NULL;
    }
    //initialize class variables
    nb_tokens=0;
    count = 0;
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
bool hasht::addToken(string name, int id){
    token* existingToken = findToken(name);
    if (existingToken != NULL) {
        //Token already exists
        return false;
    }
    int index = hash(name);
    if(HashTable[index] == NULL){
        nb_tokens = nb_tokens + 1;
        HashTable[index] = new hashToken;
        HashTable[index]->t = new token;
        HashTable[index]->t->name = name;
        HashTable[index]->t->index = id;
        HashTable[index]->t->nbDoc = 0;
        HashTable[index]->t->doc = NULL;
        HashTable[index]->t->count = 0;
        HashTable[index]->t->offset = 0;
        HashTable[index]->next = NULL;
        HashTable[index]->prev = NULL;
    }
    else{
        nb_tokens = nb_tokens + 1;
        hashToken* ptr = HashTable[index];
        hashToken* n = new hashToken;
        n->t = new token;
        n->t->name = name;
        n->t->index = id;
        n->t->nbDoc = 0;
        n->t->doc = NULL;
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
    existingToken->nbDoc=existingToken->nbDoc + 1;
    if (iter == NULL){
        existingToken->doc = doc;
        return true;
    }
    while (iter->next != NULL){
        iter=iter->next;
    }
    iter->next=doc;
    return true;

}
int hasht::numberOftokensInIndex(int index){
    int count = 0;
    if(HashTable[index] == NULL){
        return count;
    }
    count++;
    hashToken* iter=HashTable[index];
    while(iter->next != NULL){
        count++;
        iter = iter->next;
    }
    return count;
}
token* hasht::findToken(string name){
    int index = hash(name);
    hashToken* iter = HashTable[index];
    while (iter != NULL){
        if (iter->t->name == name){
            break;
        }
        iter = iter->next;
    }
    if (iter == NULL) {
        return NULL;
    }
    return iter->t;
}
hashToken* hasht::findParentToken(string name){
    int index = hash(name);
    hashToken* iter = HashTable[index];
    while (iter != NULL){
        if (iter->t->name == name){
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
void hasht::displayHashTable(){
    cout << "There are " << nb_tokens << "tokens showed" <<endl;
    for(int index=0; index<tableSize; index++){
        if(HashTable[index]!=NULL){
            hashToken*  iter = HashTable[index];
            cout << "index: " << index << endl;
            while(iter!=NULL){
                cout << "     token name: " << iter->t->name << " ** nbDoc: " << iter->t->nbDoc <<endl;
                document* doct = iter->t->doc;
                while(doct != NULL){
                    cout << "        doc id: " <<  doct->id << ", term freq: " << 
                        doct->frequency << endl;
                    doct = doct->next;
                }
                iter = iter->next;
            }
        }
    }
}
