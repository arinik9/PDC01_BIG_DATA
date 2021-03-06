#include "dataStructure.h"
#include "ReadWrite.h"
#include <math.h>
#include <vector>


//Class that handle writing of the indexes

ReadWrite::ReadWrite(std::string folder){
    this->folder = folder;
    this->root = NULL;
    this->nb_tokens = 0;
    this->toFile = NULL;
}

ReadWrite::ReadWrite(){
    this->root=NULL;
    this->nb_tokens=0;
    this->folder = "./storage/";
    this->toFile = NULL;
}

ReadWrite::~ReadWrite() {
    //TODO
}

std::string ReadWrite::getFolder(){
    return folder;
}
int ReadWrite::getNbFiles(){
    return this->nbFiles;
}
token* ReadWrite::getToken(int index){
    //Get token from a ram stored chained list. this token is the same one
    //as the one kept inside the hash table
    tokenList* iter = root;
    while (iter != NULL){
        if (iter->t->index == index){
            return iter->t;
        }
        iter = iter->next;
    }
    return NULL;
}

bool ReadWrite::write() {
    std::ofstream *file = new std::ofstream(this->getNextFileName().c_str(), std::ofstream::binary);

    if(this->folder == "" || !file->good())//error => no filename defined
        return false;

    file->write(reinterpret_cast<const char*>(&(this->nb_tokens)),sizeof(this->nb_tokens));

    tokenList* iter = root;
    while(iter != NULL) {

        if (iter->t->doc != NULL){
            this->writeToken(file,iter->t);
        }

        iter = iter->next;
    }
    
    file->close();
    delete file;
    return true;
}
bool ReadWrite::writeToken(std::ofstream* file, token* token)
{
    // write token to an already opened ofstream
    token->offset = file->tellp();
    file->write(reinterpret_cast<const char*>(&(token->index)),sizeof(token->index));
    file->write(reinterpret_cast<const char*>(&(token->nbDoc)),sizeof(token->nbDoc));

    document* it = token->doc;
    while (it != NULL) {
        file->write(reinterpret_cast<const char*>(&(it->id)),sizeof(it->id));
        file->write(reinterpret_cast<const char*>(&(it->frequency)),sizeof(it->frequency));
        it = it->next;
    }
    return true;
}

bool ReadWrite::writeToken(token* token)
{
    // Never used
    if(this->toFile == NULL)
    {
        this->toFile = new std::ofstream(getNextFileName().c_str(),std::ios::binary);
    }
    
    if(!this->toFile->good())
    {
        return false;
    }
    else
    {
       return this->writeToken(this->toFile,token);
    }
}

token* ReadWrite::readByOffset(unsigned int offset, std::ifstream* file){
    //Read token from an already opened ifstream
    file->clear();
    file->seekg(0, std::ios::beg);
    int nbTokens;
    int tokenIndex;
    int nbDoc;
    int fileId;
    int fileFreq;
    token* newToken = new token;
    file->seekg(offset, std::ios::beg);

    file->read(reinterpret_cast<char*>(&tokenIndex), sizeof(((token*)NULL)->index));
    file->read(reinterpret_cast<char*>(&nbDoc), sizeof(((token*)NULL)->nbDoc));
    newToken->index = tokenIndex;
    newToken->nbDoc = nbDoc;
    newToken->doc = NULL;

    document* iter_doc = newToken->doc;
    for(int j=0; j<nbDoc; j++){
        document* d = new document;
        file->read(reinterpret_cast<char*>(&fileId), sizeof(((document*)NULL)->id));
        file->read(reinterpret_cast<char*>(&fileFreq), sizeof(((document*)NULL)->frequency));
        d->id=fileId;
        d->frequency = fileFreq;
        d->next = NULL;
        if (iter_doc == NULL){
            newToken->doc = d;
            iter_doc = d;
        }
        else{
            while (iter_doc->next != NULL){
                iter_doc=iter_doc->next;
            }
            iter_doc->next=d;
        }
    }

    return newToken;
}

token* ReadWrite::readByIndex(int index, std::ifstream* file){
    file->clear();
    file->seekg(0, std::ios::beg);
    int nbTokens;
    int tokenIndex;
    int nbDoc;
    int fileId;
    int fileFreq;
    token* newToken;

    file->read(reinterpret_cast<char*>(&nbTokens), sizeof(nbTokens));
    if(index >= nbTokens) //error => index value can not be higher than nbTokens
        return 0;

    //jumping onto each token until arrive on index'th token
    for(int i=0; i<index; i++){
        file->read(reinterpret_cast<char*>(&tokenIndex), sizeof(((token*)NULL)->index));
        file->read(reinterpret_cast<char*>(&nbDoc), sizeof(((token*)NULL)->nbDoc));
        std::vector<char> buffer(nbDoc*2*sizeof(int));
        file->read(buffer.data(), nbDoc*2*sizeof(int));
    }
    file->read(reinterpret_cast<char*>(&tokenIndex), sizeof(((token*)NULL)->index));
    file->read(reinterpret_cast<char*>(&nbDoc), sizeof(((token*)NULL)->nbDoc));

    //now we are on index'th token
    newToken = this->getToken(tokenIndex);
    newToken->nbDoc += nbDoc;
    document* last = getLast(newToken->doc);
    document* iter_doc = newToken->doc;
    for(int j=0; j<nbDoc; j++){
        document* d = new document;
        file->read(reinterpret_cast<char*>(&fileId), sizeof(((document*)NULL)->id));
        file->read(reinterpret_cast<char*>(&fileFreq), sizeof(((document*)NULL)->frequency));
        d->id=fileId;
        d->frequency=fileFreq;
        d->next=NULL;
        if (iter_doc == NULL){
            newToken->doc = d;
            iter_doc = d;
        }
        else{
            while (iter_doc->next != NULL){
                iter_doc=iter_doc->next;
            }
            iter_doc->next=d;
        }
    }
   return newToken;
}

void ReadWrite::addToken(token* newtoken){
    // Adds token in a sorted chained list
    // Sort is done using the token's id
    tokenList* t_list = new tokenList;
    t_list->t = newtoken;
    t_list->next = NULL;

    if(root == NULL){
        root = t_list;
        this->nb_tokens = this->nb_tokens + 1;
    }
    else{//at least one token exists in the  linked list
        tokenList* ptr = root;
        tokenList* prev_ptr=root;
        bool added=false;
        while(ptr != NULL){
            if(t_list->t->index == ptr->t->index){//token already exists
                added=true;
                //token exists but it doesnt contain new doc.
                //So just update the root doc address via newtoken
                ptr->t->doc =t_list->t->doc;
                this->nb_tokens = this->nb_tokens + 1;
                break;
            }
            else if(t_list->t->index < ptr->t->index){//token doesn't exist.It is inserting now
                this->nb_tokens = this->nb_tokens + 1;
                added=true;
                if(ptr == root){
                    t_list->next=ptr;
                    root=t_list;
                    break;
                }
                t_list->next = ptr;
                prev_ptr->next = t_list;
                break;
            }
            prev_ptr = ptr;
            ptr = ptr->next;
        }
        if(!added){// token will be inserted at the end
            this->nb_tokens = this->nb_tokens + 1;
            prev_ptr->next=t_list;
            t_list->next=NULL;
        }
    }
}

void ReadWrite::display(){
    tokenList* p = root;
    while(p!=NULL){
        std::cout << p->t->index << ", " << p->t->name << std::endl;
        document* doc = p->t->doc;
        while(doc != NULL){
            std::cout << "\t" << doc->id << ", ";
            doc = doc->next;
        }
        std::cout << std::endl;
        p = p->next;
    }
}

void ReadWrite::flush(){
    //we delete just documents. So Tokens will stay in the linked list
    //we create each document by doing 'new'. So we need to delete all
    tokenList* p = root;
    while(p != NULL){
        deleteToken(p->t);
        p->t->doc = NULL;
        p = p->next;
    }
    this->nb_tokens = 0;
}


void ReadWrite::deleteToken(token* t){
    // Does not delete the token, merely resets its posting list
    document* doc1 = t->doc;
    if (t->nbDoc == 0){
        return;
    }
    while (doc1 != NULL){
        document* doc2 = doc1;
        doc1 = doc1->next;
        delete doc2;
    }
    t->nbDoc = 0;
    t->doc = NULL;
}

bool ReadWrite::closeCurrentWritingFile()
{
    this->toFile->close();
    if(!this->toFile->is_open())
    {
        delete this->toFile;
        return true;
    }
    else
    {
        return false;
    }
}
bool ReadWrite::deleteIndexFile(int i)
{
    std::string fileName = this->folder + intToString(i) + ".index";

    return std::remove(fileName.c_str());

}

bool ReadWrite::deleteTempIndexFile(int i){
   // it does not give any error even if the file does not exist
    std::string fileName = this->folder + intToString(i) + ".tempindex";

    return std::remove(fileName.c_str());
}

std::string ReadWrite::getNextFileName()
{
    this->nbFiles++;
    return this->folder + intToString(this->nbFiles) + ".index";
}

bool ReadWrite::mergeIndexes(std::string firstIndexFilename,
                             std::string secIndexFilename,
                             std::string outIndexFilename){
    //Merges to files
    
    std::ifstream firstIndex;
    std::ifstream secIndex;
    std::ofstream outIndex;
    firstIndex.open(firstIndexFilename.c_str(), std::ios::binary);
    secIndex.open(secIndexFilename.c_str(), std::ios::binary);
    outIndex.open(outIndexFilename.c_str(), std::ios::binary);
    int firstIter = 0;
    int secIter = 0;
    int firstCount;
    firstIndex.read((char*)&firstCount, sizeof(firstCount));
    int secCount;
    secIndex.read((char*)&secCount, sizeof(secCount));
    int gbCount = firstCount + secCount;
    outIndex.write(reinterpret_cast<const char*>(&(gbCount)),sizeof(gbCount));
    token* t1 = this->readByIndex(firstIter, &firstIndex);
    token* t2 = this->readByIndex(secIter, &secIndex);
    while (firstIter < firstCount || secIter < secCount){
        if (firstIter == firstCount || t1->index > t2->index){
            this->writeToken(&outIndex, t2);
            deleteToken(t2);
            secIter++;
            t2 = this->readByIndex(secIter, &secIndex);
            continue;
        }
        if (secIter == secCount || t1->index < t2->index){
            this->writeToken(&outIndex, t1);
            deleteToken(t1);
            firstIter++;
            t1 = this->readByIndex(firstIter, &firstIndex);
            continue;
        }
        // If both token have the same id, we need to reduce the total number
        // of token for the file
        gbCount--;
        this->writeToken(&outIndex, t1);
        deleteToken(t2);
        secIter++;
        t2 = this->readByIndex(secIter, &secIndex);
        deleteToken(t1);
        firstIter++;
        t1 = this->readByIndex(firstIter, &firstIndex);
    }
    firstIndex.close();
    secIndex.close();
    outIndex.seekp(0, std::ios::beg);
    outIndex.write(reinterpret_cast<const char*>(&(gbCount)),sizeof(gbCount));
    outIndex.close();
    return true;

}

bool ReadWrite::mergeFinal(std::string firstIndexFilename,
                             std::string secIndexFilename,
                             int nbTotalDocs, double* normsOfDocs){
    //Mostly the same as the previous method, but there was to much variation
    //to make one method
    std::string outIndexFilename = "final.index";
    std::ifstream firstIndex;
    std::ifstream secIndex;
    std::ofstream outIndex;
    firstIndex.open(firstIndexFilename.c_str(), std::ios::binary);
    secIndex.open(secIndexFilename.c_str(), std::ios::binary);
    outIndex.open(outIndexFilename.c_str(), std::ios::binary);
    int firstIter = 0;
    int secIter = 0;
    int firstCount;
    firstIndex.read((char*)&firstCount, sizeof(firstCount));
    int secCount;
    secIndex.read((char*)&secCount, sizeof(secCount));
    int gbCount = firstCount + secCount;
    outIndex.write(reinterpret_cast<const char*>(&(gbCount)),sizeof(gbCount));
    token* t1 = this->readByIndex(firstIter, &firstIndex);
    token* t2 = this->readByIndex(secIter, &secIndex);
    while (firstIter < firstCount || secIter < secCount){
        if (!t2){
            tfidf(t1,idf(nbTotalDocs, t1->nbDoc));
            this->writeToken(&outIndex, t1);
            //aggregating tf-idf value for each document
            document* iterDoc = t1->doc;
            while(iterDoc != NULL){
                normsOfDocs[iterDoc->id-1] += pow(iterDoc->frequency, 2);
                iterDoc = iterDoc->next;
            }
            //
            deleteToken(t1);
            firstIter++;
            t1 = this->readByIndex(firstIter, &firstIndex);
            continue;
        }
        if (!t1){
            tfidf(t2,idf(nbTotalDocs, t2->nbDoc));
            this->writeToken(&outIndex, t2);
            //aggregating tf-idf value for each document
            document* iterDoc = t2->doc;
            while(iterDoc != NULL){
                normsOfDocs[iterDoc->id-1] += pow(iterDoc->frequency, 2);
                iterDoc = iterDoc->next;
            }
            //
            deleteToken(t2);
            secIter++;
            t2 = this->readByIndex(secIter, &secIndex);
            continue;
        }

        if (firstIter == firstCount || t1->index > t2->index){
            tfidf(t2,idf(nbTotalDocs, t2->nbDoc));
            this->writeToken(&outIndex, t2);
            //aggregating tf-idf value for each document
            document* iterDoc = t2->doc;
            while(iterDoc != NULL){
                normsOfDocs[iterDoc->id-1] += pow(iterDoc->frequency, 2);
                iterDoc = iterDoc->next;
            }
            //
            deleteToken(t2);
            secIter++;
            t2 = this->readByIndex(secIter, &secIndex);
            continue;
        }
        if (secIter == secCount || t1->index < t2->index){
            tfidf(t1,idf(nbTotalDocs, t1->nbDoc));
            this->writeToken(&outIndex, t1);
            //aggregating tf-idf value for each document
            document* iterDoc = t1->doc;
            while(iterDoc != NULL){
                normsOfDocs[iterDoc->id-1] += pow(iterDoc->frequency, 2);
                iterDoc = iterDoc->next;
            }
            //
            deleteToken(t1);
            firstIter++;
            t1 = this->readByIndex(firstIter, &firstIndex);
            continue;
        }
        gbCount--;
        tfidf(t1,idf(nbTotalDocs, t1->nbDoc));
        this->writeToken(&outIndex, t1);
            //aggregating tf-idf value for each document
            document* iterDoc = t1->doc;
            while(iterDoc != NULL){
                normsOfDocs[iterDoc->id-1] += pow(iterDoc->frequency, 2);
                iterDoc = iterDoc->next;
            }
            //
        deleteToken(t2);
        secIter++;
        t2 = this->readByIndex(secIter, &secIndex);
        deleteToken(t1);
        firstIter++;
        t1 = this->readByIndex(firstIter, &firstIndex);
    }
    firstIndex.close();
    secIndex.close();
    outIndex.seekp(0, std::ios::beg);
    outIndex.write(reinterpret_cast<const char*>(&(gbCount)),sizeof(gbCount));
    outIndex.close();
    return true;
}
