#include "dataStructure.h"
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

void ReadWrite::addToken(token* newtoken){
	tokenList* t_list = new tokenList;
    t_list->t = newtoken;
    t_list->next = NULL;

    if(root == NULL){
        root = t_list;
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

void ReadWrite::removeFirstToken(){
    // Each time, we remove the head of linked list
    tokenList** head = &root;
    tokenList* ptr = *head;
    if(head){
        *head = ptr->next;

        delete ptr->t->doc;
        delete ptr->t;
        delete ptr;
    }
}

void ReadWrite::initialize(){
    tokenList* p = root;
    while(p != NULL){
        removeFirstToken();
        p= p->next;
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
