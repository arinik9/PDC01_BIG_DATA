#include <iostream>
#include <fstream>

#ifndef READWRITE_H_
#define READWRITE_H_

class ReadWrite {
private:
    std::ifstream fromFile;
    std::ofstream toFile;
    std::string folder;
    int nb_tokens;
    tokenList* root;
    bool writeToken(token* token);
public:
    bool write();
    token* read();
    token* readByIndex(int index);
	void addToken(token* newtoken);
    void initialize();
    std::string getFolder();
	void display();
	void createInvertedFileOnDisk();
	ReadWrite(std::string filename);
    ReadWrite();
	virtual ~ReadWrite();

};

#endif /* READWRITE_H_ */
