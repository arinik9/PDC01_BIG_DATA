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
#include "Request.h"
#include <math.h>
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
    int file_counter=0;
    int last_file_id=-1;
    string tokenName;
    while (true){
        string in;
        if(!getline(std::cin, in)){
            break;
        }
        counter = counter + 1;
        //cout << in <<endl;
        //string tokenName;
        document* doc = strToDoc(in, tokenName);
        if (hashy.addToken(tokenName, tokenId)){
            //add token returns false if token already exists
            tokenId++;
        }
        hashy.addDocument(tokenName, doc);
        token* newToken = hashy.findToken(tokenName);
        rw.addToken(newToken);
        //increment file counter
        if(last_file_id != doc->id){
            last_file_id = doc->id;
            file_counter += 1;
        }

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

    double normsOfDocs[file_counter];
    //initializing
    for(int z=0; z!=file_counter; z++)
        normsOfDocs[z]=0.0;

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
    rw.mergeFinal(tempIndex0, tempIndex1, whole_count, normsOfDocs);

    //deleting all small index files
    for(int i=1; i<=fileIndexCount; i++){
        rw.deleteIndexFile(i);
        rw.deleteTempIndexFile(i);
    }

    for(int y=0; y!=file_counter; y++){
        normsOfDocs[y] = sqrt(normsOfDocs[y]);
    }

    Request req;
    std::vector<std::string> vec(2); vec[0]="home"; vec[1]="page";
    cout << "Given query words: <" << vec[0] << ", " << vec[1] << ">" << endl;
    std::vector<token*> vecToken;

    std::ifstream firstIndex;
    firstIndex.open("final.index", std::ios::binary);
    for(std::vector<std::string>::iterator iterTokenName=vec.begin(); iterTokenName!=vec.end(); iterTokenName++){
    unsigned int offset = hashy.findToken(*iterTokenName)->offset;
    token* tkn = rw.readByOffset(offset, &firstIndex);
    vecToken.push_back(tkn);
    }
    firstIndex.close();

    req.query(vecToken, normsOfDocs);
    req.displayAnswers();

    //rw.display();
    //cout << endl;
    //hashy.displayHashTable();
    //cout << counter << endl;

    return 0;
}
