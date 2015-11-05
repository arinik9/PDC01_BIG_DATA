#include "dataStructure.h"
#include "ReadWrite.h"
#include <vector>

ReadWrite::ReadWrite(std::string folder){
    this->folder = folder;
    this->root = NULL;
    this->nb_tokens = 0;
}

ReadWrite::ReadWrite(){
	this->root=NULL;
    this->nb_tokens=0;
    this->filename = "";
}

ReadWrite::~ReadWrite() {
    //TODO
}

std::string ReadWrite::getFilename(){
    return filename;
}

bool ReadWrite::write() {
    //TODO Add exception handling
    //TODO it is possibile that we should change the type of 'this->nb_tokens' from int to uint32
    if(this->filename == "")//error => no filename defined
        return 0;

    this->toFile.write(reinterpret_cast<const char*>(&(this->nb_tokens)),sizeof(this->nb_tokens));

    tokenList* iter = root;
    while(iter != NULL) {
        this->toFile.write(reinterpret_cast<const char*>(&(iter->t->index)),sizeof(iter->t->index));
        this->toFile.write(reinterpret_cast<const char*>(&(iter->t->nbDoc)),sizeof(nbDocs));

        document* it = iter->t->doc;
        while (it != NULL) {
            this->toFile.write(reinterpret_cast<const char*>(&(it->id)),sizeof(it->id));
            this->toFile.write(reinterpret_cast<const char*>(&(it->frequency)),sizeof(it->frequency));
            it = it->next;
        }

        iter = iter->next;
    }
    
    this->toFile.close();
    return true;
}

token* ReadWrite::readByIndex(int index){
    //Index values begin from 0
    if(this->filename == "")// error => no filename defined
        return 0;
    fromFile.open(filename.c_str(), std::ios::binary);
    int nbTokens;
    int tokenIndex;
    int nbDoc;
    int fileId;
    int fileFreq;
    token* newToken = new token;
    newToken->doc = NULL;

    fromFile.read(reinterpret_cast<char*>(&nbTokens), sizeof(int));
    if(index>nbTokens) //error => index value can not be higher than nbTokens
        return 0;

    //jumping onto each token until arrive on index'th token
    for(int i=0; i<=index; i++){
        fromFile.read(reinterpret_cast<char*>(&tokenIndex), sizeof(int));
        fromFile.read(reinterpret_cast<char*>(&nbDoc), sizeof(int));
        std::vector<char> buffer(nbDoc*2*sizeof(int));
        fromFile.read(buffer.data(), nbDoc*2*sizeof(int));
    }

    //now we are on index'th token
    newToken->index=tokenIndex;
    newToken->nbDoc=nbDoc;
    for(int j=0; j<nbDoc; j++){
        document* d = new document;
        fromFile.read(reinterpret_cast<char*>(&fileId), sizeof(int));
        fromFile.read(reinterpret_cast<char*>(&fileFreq), sizeof(int));
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

void ReadWrite::initialize(){
    //we delete just documents. So Tokens will stay in the linked list
    //we create each document by doing 'new'. So we need to delete all
    tokenList* p = root;
    while(p != NULL){
        document** headdoc = &(p->t->doc);
        while(*headdoc != NULL){
            document* ptr = *headdoc;
            *headdoc = ptr->next;
            delete ptr;
        }
        p = p->next;
    }
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
