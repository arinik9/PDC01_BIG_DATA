#include <iostream>
#include <sstream>  
// Contains various methods and struct used in program

struct document{
   int id;
   int frequency;
   // Frequency is used to store various data, including tfidf
   document* next;
   //int tf;
   //int idf;
};

// We have 3 token struct, one which is the actual token, the others are just
// chained list. We use those three structures in order to keep our token index
// void of influence from both of the chained list. That way, we get to have
// the same address stored in the lists all the time
struct token{
   int index;
   std::string name;
   unsigned int nbDoc;
   document * doc;
   unsigned int offset;
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
struct answer{
	int docId;
	double score;
};
std::string intToString(int i);
document* getLast(document* first);
int idf(int nbTotal, int nb);
void tfidf(token* t, int idfValue);
