#include "dataStructure.h"
#include "ReadWrite.h"
#include <vector>

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
    //TODO Add exception handling
    //TODO it is possibile that we should change the type of 'this->nb_tokens' from int to uint32

    std::ofstream *file = new std::ofstream(this->getNextFileName().c_str(), std::ofstream::binary);

    if(this->folder == "" || !file->good())//error => no filename defined
        return false;

    file->write(reinterpret_cast<const char*>(&(this->nb_tokens)),sizeof(this->nb_tokens));

    tokenList* iter = root;
    while(iter != NULL) {

        this->writeToken(file,iter->t);

        iter = iter->next;
    }
    
    file->close();
    delete file;
    return true;
}
bool ReadWrite::writeToken(std::ofstream* file, token* token)
{
    file->write(reinterpret_cast<const char*>(&(token->index)),sizeof(token->index));
    file->write(reinterpret_cast<const char*>(&(token->nbDoc)),sizeof(token->nbDoc));

    document* it = token->doc;
    while (it != NULL) {
        file->write(reinterpret_cast<const char*>(&(it->id)),sizeof(it->id));
        file->write(reinterpret_cast<const char*>(&(it->frequency)),sizeof(it->frequency));
        std::cout << "writedoc " << token->index << "|" << token->name << " " << it->id << std::endl;
        it = it->next;
    }
    return true;
}

bool ReadWrite::writeToken(token* token)
{
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

token* ReadWrite::readByIndex(int index){
    //TODO Open file

    //Index values begin from 0
    /*if(this->filename == "")// error => no filename defined
        return 0;*/
    //fromFile.open(filename.c_str(), std::ios::binary);
    int nbTokens;
    int tokenIndex;
    int nbDoc;
    int fileId;
    int fileFreq;
    token* newToken = new token;
    newToken->doc = NULL;

    fromFile.read(reinterpret_cast<char*>(&nbTokens), sizeof(nbTokens));
    if(index>nbTokens) //error => index value can not be higher than nbTokens
        return 0;

    //jumping onto each token until arrive on index'th token
    for(int i=0; i<=index; i++){
        fromFile.read(reinterpret_cast<char*>(&tokenIndex), sizeof(((token*)NULL)->index));
        fromFile.read(reinterpret_cast<char*>(&nbDoc), sizeof(((token*)NULL)->nbDoc));
        std::vector<char> buffer(nbDoc*2*sizeof(int));
        fromFile.read(buffer.data(), nbDoc*2*sizeof(int));
    }

    //now we are on index'th token
    newToken->index=tokenIndex;
    newToken->nbDoc=nbDoc;
    for(int j=0; j<nbDoc; j++){
        document* d = new document;
        fromFile.read(reinterpret_cast<char*>(&fileId), sizeof(((document*)NULL)->id));
        fromFile.read(reinterpret_cast<char*>(&fileFreq), sizeof(((document*)NULL)->frequency));
        d->id=fileId;
        d->frequency=fileFreq;
        d->next=NULL;
        document* iter_doc = newToken->doc;
        if (iter_doc == NULL){
            newToken->doc = d;
        }
        else{
            while (iter_doc->next != NULL){
                iter_doc=iter_doc->next;
            }
            iter_doc->next=d;
        }
    }
   fromFile.close();
   return newToken;
}

void ReadWrite::addToken(token* newtoken){
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

void ReadWrite::createInvertedFileOnDisk() {
    //Write to a binary file
 /*   int test = 2;
    toFile.write(reinterpret_cast<const char*>(&test), sizeof(int));
    toFile.close();


    fromFile.open(filename.c_str(), std::ios::binary);
    int t;
    fromFile.read(reinterpret_cast<char*>(&t), sizeof(int));
    fromFile.close();
    std::cout << "output from " << filename << ": " << t << std::endl;
*/
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
std::string ReadWrite::getNextFileName()
{
    this->nbFiles++;
    return this->folder + intToString(this->nbFiles) + ".index";
}
