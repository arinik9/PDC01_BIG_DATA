
struct document{
   int id;
   int tf;
   int idf;
};
struct token{
   int index;
   std::string name;
   document * doc;
};
struct tokenHash{
   token* t;
   tokenHash* next;
   tokenHash* prev;
};