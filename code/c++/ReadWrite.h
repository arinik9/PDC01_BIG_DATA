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
    bool write(std::string filename);
    token* readByIndex(std::string filename, int index);
	void addToken(token* newtoken);
    std::string getFolder();
    void flush();
	void display();
	void createInvertedFileOnDisk();
    ReadWrite();
	virtual ~ReadWrite();

};

#endif /* READWRITE_H_ */
