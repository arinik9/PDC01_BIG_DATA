#include "ReadWrite.h"

ReadWrite::ReadWrite(std::string filename):toFile(filename.c_str(), std::ios::binary) {
    this->filename = filename;
	root=NULL;
}

ReadWrite::ReadWrite(){
	root=NULL;
}

ReadWrite::~ReadWrite() {
    //TODO
}

std::string ReadWrite::getFilename(){
    return filename;
}

void ReadWrite::addToken(int token_id, int doc_id, int frequency){
	Token* token = new Token;
    token->token_id=token_id;
    token->doc_id=doc_id;
    token->frequency=frequency;

    if(root == NULL){
	    token->next=NULL;
        token->prev=NULL;
        root = token;
    }
    else{
        Token* ptr = root;
        Token* prev_ptr=root;
        bool added=false;
        while(ptr != NULL){
            bool comp = (token->token_id < ptr->token_id);
            bool comp1 = (token->token_id == ptr->token_id);
            bool comp2 = (token->doc_id < ptr->doc_id);
            if(comp1) comp = comp2;

            if(comp){
                added=true;
                if(ptr->prev==NULL){
                    token->next=ptr;
                    ptr->prev=token;
                    root=token;
                    break;
                }
                token->next = ptr;
                Token* p1 = ptr->prev;
                ptr->prev = token;
                token->prev=p1;
                p1->next=token;
                break; 
            }
            prev_ptr = ptr;
            ptr = ptr->next;
        }
        if(!added){
            prev_ptr->next=token;
            token->prev=prev_ptr;
            token->next=NULL;
        }
    }
}

void ReadWrite::display(){
    Token* p = root;
	while(p!=NULL){
        std::cout << p->token_id << "," << p->doc_id << std::endl;
	    p = p->next;
	}
}

void ReadWrite::removeFirstToken(){
    // Each time, we remove the head of linked list
    Token** head = &root;
    Token* ptr = *head;
    if(head){
        *head = ptr->next;
        delete ptr;
    }
}

void ReadWrite::initialize(){
    Token* p = root;
    while(p != NULL){
        removeFirstToken();
        p= p->next;
    }
}

void ReadWrite::createInvertedFileOnDisk() {
    //Write to a binary file
    int test = 2;
    toFile.write(reinterpret_cast<const char*>(&test), sizeof(int));
    toFile.close();


    fromFile.open(filename.c_str(), std::ios::binary);
    int t;
    fromFile.read(reinterpret_cast<char*>(&t), sizeof(int));
    fromFile.close();
    std::cout << "output from " << filename << ": " << t << std::endl;

}
