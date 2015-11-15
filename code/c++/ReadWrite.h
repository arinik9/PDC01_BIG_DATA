#include <iostream>
#include <fstream>

#ifndef READWRITE_H_
#define READWRITE_H_

class ReadWrite {
private:
    std::ifstream fromFile;
    std::ofstream* toFile;
    std::string folder;
    int nb_tokens;
    tokenList* root;
    int nbFiles;
    bool writeToken(std::ofstream* file, token* token);
    std::string getNextFileName();
    token* getToken(int index);
    void deleteToken(token* t);

public:
    bool write();
    bool writeToken(token* token);
    token* read();
    token* readByIndex(int index, std::ifstream* file);
    token* readByOffset(unsigned int index, std::ifstream* file);
	void addToken(token* newtoken);
    void flush();
    std::string getFolder();
	void display();
    bool deleteIndexFile(int id);
    bool deleteTempIndexFile(int id);
    bool closeCurrentWritingFile();
    bool mergeIndexes(std::string firstIndexFilename,
                      std::string secIndexFilename,
                      std::string outIndexFilename);
    bool mergeFinal(std::string firstIndexFilename,
                    std::string secIndexFilename,
                    int nbTotalDocs, double* normsOfDocs);
    int getNbFiles();
	ReadWrite(std::string folder);
    ReadWrite();
	virtual ~ReadWrite();


};

#endif /* READWRITE_H_ */
