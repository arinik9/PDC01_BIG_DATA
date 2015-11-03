#include <iostream>

struct document{
   int id;
   int frequency;
   document* next;
   //int tf;
   //int idf;
};
struct token{
   int index;
   std::string name;
   document * doc;
   unsigned int count : 16;
   unsigned int offset : 10;
};
struct hashToken{
   hashToken* prev;
   hashToken* next;
   token* t;
};
struct tokenList{
  token* t;
  tokenList* next;
};
