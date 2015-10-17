/* 
 * File:   main.cpp
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 19:44
 */

#include <iostream>
#include "hasht.h"

using namespace std;

int main(int argc, char** argv) {
    hasht hashy;

    document* monty1 = new document;
    document* monty2 = new document;
    document* monty3 = new document;
    document* monty4 = new document;
    monty1->id = 0;
    monty2->id = 0;
    monty3->id = 0;
    monty4->id = 0;
    monty1->next = NULL;
    monty2->next = NULL;
    monty3->next = NULL;
    monty4->next = NULL;
    monty1->frequency = 1;
    monty2->frequency = 2;
    monty3->frequency = 3;
    monty4->frequency = 4;
    monty1->name = "Monty Python Quotes";
    monty2->name = "Monty Python Quotes";
    monty3->name = "Monty Python Quotes";
    monty4->name = "Monty Python Quotes";
    
    document* scarface1 = new document;
    document* scarface2 = new document;
    document* scarface3 = new document;
    document* scarface4 = new document;
    scarface1->id = 1;
    scarface2->id = 1;
    scarface3->id = 1;
    scarface4->id = 1;
    scarface1->next = NULL;
    scarface2->next = NULL;
    scarface3->next = NULL;
    scarface4->next = NULL;
    scarface1->frequency = 1;
    scarface2->frequency = 2;
    scarface3->frequency = 3;
    scarface4->frequency = 4;
    scarface1->name = "Scarface Quotes";
    scarface2->name = "Scarface Quotes";
    scarface3->name = "Scarface Quotes";
    scarface4->name = "Scarface Quotes";

    hashy.AddToken("nobody",        monty1);
    hashy.AddToken("expects",       monty2);
    hashy.AddToken("spanish",       monty3);
    hashy.AddToken("inquisition",   monty4);
    hashy.AddToken("say",           scarface1);
    hashy.AddToken("hello",         scarface2);
    hashy.AddToken("litle",         scarface3);
    hashy.AddToken("friend",        scarface4);

   token* say = hashy.FindToken("say"); 
   cout << say->name << endl;
   cout << say->doc->name << endl;
   return 0;
}
