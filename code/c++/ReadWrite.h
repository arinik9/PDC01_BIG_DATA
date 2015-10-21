#include <iostream>
#include <fstream>

#ifndef READWRITE_H_
#define READWRITE_H_

struct Token
{
    int token_id;
    int doc_id;
    int frequency;
    Token* next;
    Token* prev;
};


class ReadWrite {
private:
    std::ifstream fromFile;
    std::ofstream toFile;
    std::string filename;
    Token* root;
public:

	void addToken(int token_id, int doc_id, int frequency);
    void removeFirstToken();
    void initialize();
    std::string getFilename();
	void display();
	void createInvertedFileOnDisk();
	ReadWrite(std::string filename);
    ReadWrite();
	virtual ~ReadWrite();

};

#endif /* READWRITE_H_ */
