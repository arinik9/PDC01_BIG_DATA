#include "dataStructure.h"
#include <string>
#include <sstream>
std::string intToString(int i)
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

document* getLast(document* first){
    //Return iterator to the end of a posting list
    if (first == NULL){
        return NULL;
    }
    document* doc = first;
    while (doc->next != NULL){
        doc = doc->next;
    }
    return doc;
}

int idf(int nbTotal, int nb){
    // calculate int idf
    int before_log = nbTotal/nb;
    int log_result = 0;
    while (before_log >>=1){
        log_result++;
    }
    return log_result;
}

void tfidf(token* t, int idfValue){
    document* iter = t->doc;
    while (iter != NULL){
        iter->frequency = iter->frequency * idfValue;
        //std::cout << t->name << iter->frequency << std::endl;
        iter = iter->next;
    }
}

