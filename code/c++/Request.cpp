#include "dataStructure.h"
#include "hasht.h"
#include "Request.h"
#include <map>
#include <algorithm>    // std::sort
#include <math.h>

static bool sort_using_greater_than(answer u, answer v){
       return u.score > v.score;
}

Request::Request(){
    //TODO
}
std::vector<answer> Request::query(std::vector<token*> & queryMembers, double* normsOfDocs)
{
	std::map<int,std::vector<double> > components;
    double sumTfIdfForEachToken[queryMembers.size()];
    for(int i=0; i<queryMembers.size(); i++)
        sumTfIdfForEachToken[i]=0.0; //initializing

	for(std::vector<token*>::iterator it = queryMembers.begin();it != queryMembers.end(); it++) {

		document* itDoc = (*it)->doc;
		while(itDoc !=NULL) {
            sumTfIdfForEachToken[it - queryMembers.begin()]+=itDoc->frequency;

			std::map<int,std::vector<double> >::iterator component = components.find(itDoc->id);
			if(component == components.end()) {
				std::vector<double> newComponent(queryMembers.size(),0.0);
				newComponent.at(it - queryMembers.begin()) = itDoc->frequency/normsOfDocs[itDoc->id-1];
				components.insert( std::pair<int,std::vector<double> >(itDoc->id,newComponent));

			}
			else {
				components[itDoc->id].at(it - queryMembers.begin()) = itDoc->frequency/normsOfDocs[itDoc->id-1];
			}
			itDoc = itDoc->next;
		}
	}
    
    //computing the norm value for normalizing the query vector
    // Now we know how many different files existant in our map
    double normalizedQuery[queryMembers.size()];
    double normQuery=0.0;
    for(int i=0; i<queryMembers.size(); i++){
        sumTfIdfForEachToken[i]/=components.size();
        normQuery += pow(sumTfIdfForEachToken[i], 2);    
    }
    normQuery = sqrt(normQuery);
    //normalizing each tf-idf value in the query vector
    for(int i=0; i<queryMembers.size(); i++){
        normalizedQuery[i] = sumTfIdfForEachToken[i]/normQuery;
    }
        

	for(std::map<int, std::vector<double> >::iterator itAnswr = components.begin();itAnswr != components.end(); itAnswr++) {
        answer a;
        a.docId = itAnswr->first;
        a.score=0.0;
        for(std::vector<double>::iterator itr = itAnswr->second.begin(); itr!=itAnswr->second.end(); itr++){
            a.score += (*itr) * normalizedQuery[itr - itAnswr->second.begin()];
        }
        this->answers.push_back(a);
    }

    std::sort(this->answers.begin(), this->answers.end(), sort_using_greater_than);
    return this->answers;
}

void Request::displayAnswers(){
    for(std::vector<answer>::iterator itAns = answers.begin(); itAns!=answers.end(); itAns++){
        std::cout << "file id:" << (*itAns).docId << ", score: " << (*itAns).score << std::endl;
                }
}
