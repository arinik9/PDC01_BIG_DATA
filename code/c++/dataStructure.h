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