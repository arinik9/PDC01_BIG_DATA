#include <iostream>
#include <fstream>

#ifndef READWRITE_H_
#define READWRITE_H_

class ReadWrite {
private:
    std::ifstream fromFile;
    std::ofstream toFile;
    std::string filename;
    tokenList* root;
    bool writeToken(token* token);
public:
    bool write(tokenList* list);
	void addToken(token* newtoken);
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
