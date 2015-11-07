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
#define DOC_MAX 100

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
    ReadWrite rw("invertedFile.bin");
    int counter=0;
    int tokenId = 0;
    while (true){
        counter = counter + 1;
        string in;
        if(!getline(std::cin, in)){
            break;
        }
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
        //Flush posting lists
        //Flush ReadWrite's chained list
        //cout << counter << endl;
        counter = 0;
    }
    //merge
    // finalindex = copyofindex0
    /* for (i=1; i<nbofindex; i++){
     *      currentindex = i;
     *      finalIndex2 = new index;
     *      token* iterFinal = rw.load(finalindex)
     *      token* iterCurrent = rw.load(currentIndex)
     *      while (iterFinal != NULL && iterCurrent != NULL){
     *           if (iterFinal->index < iterCurrent->index ){
     *               rw.write(iterFinal,finalIndex2)
     *               iterFinal = rw.load(iterFinal->next)
     *               continue
     *           }
     *           if (iterFinal->index > iterCurrent->index) {
     *              rw.write(interCurrent,finalIndex2)
     *              iterCurrent = rw.load(iterCurrent->next)
     *              continue
     *           }
     *          //reached if iterFinal == iterCurrent
     *          token* iterMerged = merge(iterFinal, IterCurrent)
     *          rw.write(interMerged, finalIndex2)
     *          iterCurrent = rw.load(iterCurrent->next)
     *          iterFinal = rw.load(iterFinal->next)
     *          //close indexes
     *          finalIndex = finalIndex2
     *      }
     *
     * }
     */

    //rw.display();
    //cout << endl;
    //hashy.displayHashTable();
    //cout << counter << endl;

    return 0;
}
