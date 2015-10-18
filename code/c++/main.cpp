/*
* File: main.cpp
* Author: Ghada
*
* Created on 10 octobre 2015, 19:44
*/
#define STR_SIZE 4
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "hasht.h"
#include <cstdlib>

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
    doc->name = v[2];
    doc->frequency = atoi(v[3].c_str());
    return doc;
}

int main(int argc, char** argv) {
    hasht hashy;
    while (true){
        string in;
        if(!getline(std::cin, in))
            break;
        cout << in <<endl;
        string tokenName;
        document* doc = strToDoc(in, tokenName);
        if (!hashy.addToken(tokenName, *doc)){
            hashy.addDocument(tokenName, *doc);
            //cout << doc->name << endl;
        }
    }
    return 0;
}
