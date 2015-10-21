#include <iostream>
#include <string>
#include "ReadWrite.h"

using namespace std;

int main(int argc, char** argv) {

   //Testing Read-Write functionality on binary files 
    string filename="./test.bin";
    ReadWrite rw(filename);
    //createInvertedFileOnDisk() method writes an integer (in this example it is '2') to binary file 
    //whose the name is given by 'filename' variable and reads an integer from the samefile
    rw.createInvertedFileOnDisk();
    // output is '2'


//Testing inserting and initializing functionality
/*    ReadWrite rw;
    int token_id=8;
    int doc_id=1;
    int frequency=44;
    rw.addToken(token_id, doc_id, frequency);

    token_id=4;
    doc_id=7;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);

    token_id=4;
    doc_id=1;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);

    token_id=6;
    doc_id=1;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);

    token_id=4;
    doc_id=5;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);

    token_id=10;
    doc_id=5;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);

    rw.display();

    rw.initialize();
    rw.display();

    std::cout << "INITIALIZE" << std::endl;

    token_id=4;
    doc_id=5;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);

    token_id=10;
    doc_id=5;
    frequency=22;
    rw.addToken(token_id, doc_id, frequency);
    rw.display();

    std::cout << "END" << std::endl;
*/
    return 0;
}
