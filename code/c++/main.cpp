/*
* File: main.cpp
* Author: Ghada
*
* Created on 10 octobre 2015, 19:44
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstdlib>
#include "dataStructure.h"
#include "hasht.h"
#include "ReadWrite.h"
#define STR_SIZE 3
#define DOC_MAX 10

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
    hasht hashy("tokens.bin");
    ReadWrite rw;
    int counter=0;
    int whole_count =0;
    int tokenId = 0;
    while (true){
        string in;
        if(!getline(std::cin, in)){
            break;
        }
        counter = counter + 1;
        //cout << in <<endl;
        string tokenName;
        document* doc = strToDoc(in, tokenName);
        if (hashy.addToken(tokenName, tokenId)){
            //add token returns false if token already exists
            tokenId++;
        }
        hashy.addDocument(tokenName, doc);
        token* newToken = hashy.findToken(tokenName);
        rw.addToken(newToken);
        if (counter < DOC_MAX){
            continue;
        }
        // Reached if we get more docs than we are supposed to
        

        //Write to disk
        rw.write();
        rw.flush();
        //Flush posting lists
        //Flush ReadWrite's chained list
        //cout << counter << endl;
        whole_count += counter;
        counter = 0;
    }
    whole_count += counter;
    rw.write();
    rw.flush();
    int fileIndexCount = rw.getNbFiles();
    //fileIndexCount = rw.fileIndexCount
    //
    //merge
    // string tempIndex = index(0)
    // token* t = rw.read(0,tempIndex)
    std::string tempIndex0 = rw.getFolder() + intToString(1) + ".index";
    int i;
    for (i=2; i < fileIndexCount; i++){
        std::string tempIndex1 = rw.getFolder() + intToString(i) + ".index";
        std::string outIndex = rw.getFolder() + intToString(i) + ".tempindex";
        if (!rw.mergeIndexes(tempIndex0, tempIndex1, outIndex)){
            return 0;
        }
        tempIndex0 = outIndex;
    }
    std::string tempIndex1 = rw.getFolder() + intToString(i) + ".index";
    rw.mergeFinal(tempIndex0, tempIndex1, whole_count);
    token* test = hashy.findToken("fallout");
    string fallout = "time";
    std::ifstream firstIndex;
    firstIndex.open("time", std::ios::binary);
    cout << "time " << test->index << " " << rw.readByIndex(test->index, &firstIndex)->doc->frequency << endl;
    firstIndex.close();

    //rw.display();
    //cout << endl;
    //hashy.displayHashTable();
    //cout << counter << endl;

    return 0;
}
