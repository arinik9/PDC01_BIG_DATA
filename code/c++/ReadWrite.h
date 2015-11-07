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
    int nbFiles;
    std::string getNextFileName();
public:
    bool write();
    bool writeToken(token* token);
    token* read();
    token* readByIndex(int index);
	void addToken(token* newtoken);
    void flush();
    std::string getFolder();
	void display();
	void createInvertedFileOnDisk();
	ReadWrite(std::string filename);
    ReadWrite();
	virtual ~ReadWrite();

};

#endif /* READWRITE_H_ */
