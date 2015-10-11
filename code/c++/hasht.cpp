#include <cstdlib>
#include <iostream>
#include <string>
#include "hasht.h"

using namespace std;
hasht::hasht(){
    for(int i = 0; i < tableSize; i++)
    {
        HashTable[i] = new item;
        HashTable[i]->name = "empty";
        HashTable[i]->drink = "empty";
        HashTable[i]->next = NULL;
    }
}
int hasht::Hash(string key){
    int index;
    int hash=0;
    for(int i = 0; i<key.length();i++){
        hash =(hash + (int)key[i])*17;
    }
        index = hash % tableSize; 
        return index;
}
void hasht::AddItem(string name, string drink){
    int index = Hash(name);
    if(HashTable[index]->name == "empty"){
        HashTable[index]->name = name;
        HashTable[index]->drink = drink;
    }
    else{
        item* Ptr = HashTable[index];
        item* n = new item;
        n->name = name;
        n->drink = drink;
        n->next = NULL;
        while(Ptr->next != NULL){
            Ptr = Ptr->next;
        }
        Ptr->next = n;
    }
}
int hasht::NumberOfItemsInIdex(int index){
    
    int count = 0;
    if(HashTable[index]->name == "empty"){
        return count;
    }
    else{
        count++;
        item* Ptr=HashTable[index];
        while(Ptr->next != NULL){
            count++;
            Ptr = Ptr->next;
        }
    }
    return count;
}
void hasht::PrintTable(){
    int number;
    for(int i = 0; i < tableSize; i++)
    {
        number = NumberOfItemsInIdex(i);
        cout<<"----------\n";
        cout<<"index = "<<i<<endl;
        cout<<HashTable[i]->name <<endl;
        cout<<HashTable[i]->drink <<endl;
        cout<<"# of items = " << number<<endl;
        cout<<"----------\n";
       
    }
}
void hasht::PrintItemsInIndex(int index){
    item* Ptr = HashTable[index];
    if(Ptr->name =="empty"){
        cout<<"index = "<<index<<" is empty\n";
    }
    else{
    cout<<"index "<<index<<"contains the following item\n";
    while(Ptr != NULL){
        cout<<"----------\n";
        cout<<Ptr->name <<endl;
        cout<<Ptr->drink <<endl;
        cout<<"----------\n";
        Ptr = Ptr->next;
       
    }
    }
}
void hasht::FindDrink(string name){
    int index = Hash(name);
    bool foundName = false;
    string drink;
    item* Ptr = HashTable[index];
    while(Ptr != NULL)
    {
        if(Ptr->name == name){
            foundName = true;
            drink = Ptr->drink;
        }
        Ptr = Ptr->next;
    }
    if(foundName == true){
        cout<< "favorite drink is "<<drink<<endl;
    }
    else{
        cout<<name<< "'is information was not found in the Hash Table\n";
    }
}
void hasht::RemoveItem(string name){
    int index = Hash(name);
    item* delPtr;
    item* p1;
    item* p2;
    //Case0: bucket is empty
    if(HashTable[index]->name == "empty" && HashTable[index]->drink == "empty"){
        cout<<name<< " was not found\n";
    }
    //case1: Only item contained in bucket and that item has matching name
    else if(HashTable[index]->name == name && HashTable[index]->next == NULL){
        HashTable[index]->name = "empty";
        HashTable[index]->drink = "empty";
        cout<<name<< " was removed from the hash table\n";

    }
    //case2: match is located in the first item in the bucket but there 
    //are more items in the bucket
    else if(HashTable[index]->name == name){
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr; 
        cout<<name<< " was removed from the hash table\n";

    }
    //case3:bucket contains items but first item is not a match
    else{
        p1 = HashTable[index]->next;
        p2 = HashTable[index];
        while(p1 != NULL && p1->name != name){
            p2 = p1;
            p1 = p1->next;
        }
    
    //case3.1:no match
    if(p1 == NULL){
        cout<<name<< " was not found\n";
    }
    //case3.2:match is found
    else{
    delPtr = p1;
    p1 = p1->next;
    p2->next = p1;
    delete delPtr;
    cout<<name<< " was removed from the hash table\n";

    }
    }
}