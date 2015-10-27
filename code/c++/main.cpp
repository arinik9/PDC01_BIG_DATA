/*
* File: main.cpp
* Author: Ghada
*
* Created on 10 octobre 2015, 19:44
*/
#define STR_SIZE 3
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include "dataStructure.h"
#include "hasht.h"
#include "ReadWrite.h"

using namespace std;


document* strToDoc(string str, string &tokenName){
    vector<string> v;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        v.push_back(item);
    }
    if (v.size() != STR_SIZE){
        //Someting is wrong with recieved data
        tokenName = "";
        return NULL;
    }
    tokenName = v[0];
    document* doc = new document;
    doc->id = atoi(v[1].c_str());
    doc->frequency = atoi(v[2].c_str());
    doc->next = NULL;
    return doc;
}

int main(int argc, char** argv) {
    hasht hashy;
    ReadWrite rw;
    int counter=0;
    while (true){
        counter = counter + 1;
        string in;
        if(!getline(std::cin, in))
            break;
        //cout << in <<endl;
        string tokenName;
        document* doc = strToDoc(in, tokenName);
        hashy.addToken(tokenName);
        hashy.addDocument(tokenName, doc);
        token* newToken = hashy.findToken(tokenName);
        rw.addToken(newToken);
    }

    //rw.display();
    //cout << endl;
    //hashy.displayHashTable();

    return 0;
}
