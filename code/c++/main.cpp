/* 
 * File:   main.cpp
 * Author: Ghada
 *
 * Created on 10 octobre 2015, 19:44
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "hasht.h"

using namespace std;

int main(int argc, char** argv) {
    
 hasht Hashy;
 string name="";
 Hashy.AddItem("Paul","Water");
 Hashy.AddItem("Jean","Coffee");
 Hashy.AddItem("Ghada","Jus");
 Hashy.AddItem("Nejat","Pepsi");
 Hashy.AddItem("Quentin","Cappuccino");
 Hashy.AddItem("Denis","Coca");
 
 Hashy.PrintItemsInIndex(2);

 while(name != "exit")
 {
     cout<<"remove ";
     cin>> name;
     if(name != "exit")
     {
         Hashy.RemoveItem(name);
     }
 }
 
 Hashy.PrintItemsInIndex(2);
    
    
    
    

    return 0;
}

