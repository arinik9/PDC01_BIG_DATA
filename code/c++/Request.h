#ifndef REQUEST_H_
#define REQUEST_H_
#include <vector>
class Request {

public:
	std::vector<answer>	query(std::vector<token*> &, double* normsOfDocs);
	Request();
    void displayAnswers();
private:
    std::vector<answer> answers;
};

//struct answer{ int docId; int score;}

#endif /* REQUEST_H_ */
