#include "dataStructure.h"
#include "hasht.h"
#include "request.h"
#include <map>
Request::Request(hasht* hashTable)
{
	this->hashTable = hashTable;
}
std::vector<answer> Request::query(std::vector<token> queryMembers)
{
	std::map<int,std::vector<int> > components;


	for(std::vector<token>::iterator it = queryMembers.begin();it != queryMembers.end(); it++)
	{
		token * tmpToken = this->hashTable->findToken(it->name);

		document* itDoc = tmpToken->doc;
		while(itDoc !=NULL)
		{
			std::map<int,std::vector<int> >::iterator component = components.find(itDoc->id);
			if(component == components.end())
			{
				std::vector<int> newComponent(queryMembers.size(),0);
				newComponent.at(it - queryMembers.begin()) = itDoc->frequency;
				components.insert( std::pair<int,std::vector<int> >(itDoc->id,newComponent));

			}
			else
			{
				component->second.at(it - queryMembers.begin()) = itDoc->frequency;
			}
			itDoc = itDoc->next;
		}
	}
}