/*
* File: main.cpp
* Author: Ghada
*
* Created on 10 octobre 2015, 19:44
*/
#define STR_SIZE 4
#include <iostream>
#include <string>
#include "ReadWrite.h"

using namespace std;

int main(int argc, char** argv) {

/*    std::string filename="./test.bin";
    ReadWrite rw(filename);
    rw.createInvertedFileOnDisk();
*/

    ReadWrite rw;
    int token_id=8;
    std::string token_name="edit";
    int doc_id=1;
    int frequency=6;

    // ************* //
    token* newtoken = new token;
    newtoken->id=token_id;
    newtoken->name = token_name;
    newtoken->doc = NULL;

    document* newdoc = new document;
    newdoc->id=doc_id;
    newdoc->frequency=frequency;
    newdoc->next = NULL;

    newtoken->doc = newdoc;

    rw.addToken(newtoken);
    // ********** //


    // ********* //
    token_id=8;
    token_name="edit";
    doc_id=4;
    frequency=4;

    newdoc = new document;
    newdoc->id=doc_id;
    newdoc->frequency=frequency;
    newdoc->next = NULL;

    document* headdoc=newtoken->doc;
    headdoc->next = newdoc;

    rw.addToken(newtoken);
    // *******  //


    // *******  //
    token_id=6;
    token_name="computer";
    doc_id=8;
    frequency=4;

    token* newtoken2 = new token;
    newtoken2->id=token_id;
    newtoken2->name = token_name;
    newtoken2->doc = NULL;

    newdoc = new document;
    newdoc->id=doc_id;
    newdoc->frequency=frequency;
    newdoc->next = NULL;

    newtoken2->doc = newdoc;

    rw.addToken(newtoken2);
    // *******  //


    // *******  //
    token_id=10;
    token_name="dell";
    doc_id=88;
    frequency=2;

    token* newtoken3 = new token;
    newtoken3->id=token_id;
    newtoken3->name = token_name;
    newtoken3->doc = NULL;

    newdoc = new document;
    newdoc->id=doc_id;
    newdoc->frequency=frequency;
    newdoc->next = NULL;

    newtoken3->doc = newdoc;

    rw.addToken(newtoken3);
    // *******  //

    rw.display();

    rw.removeFirstToken();

    rw.display();

    rw.initialize();
    rw.display();
    std::cout << "INITIALIZE" << std::endl;

    std::cout << "END" << std::endl;

    return 0;
}
