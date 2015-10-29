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
public:
	void addToken(token* newtoken);
    void initialize();
    std::string getFilename();
	void display();
	void createInvertedFileOnDisk();
	ReadWrite(std::string filename);
    ReadWrite();
	virtual ~ReadWrite();

};

#endif /* READWRITE_H_ */
