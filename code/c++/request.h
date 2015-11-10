#ifndef REQUEST_H_
#define REQUEST_H_
#include <vector>
class Request {

public:
	std::vector<answer>	query(std::vector<token>);
	Request(hasht* hashTable);
private:
	hasht* hashTable;
};

#endif /* REQUEST_H_ */