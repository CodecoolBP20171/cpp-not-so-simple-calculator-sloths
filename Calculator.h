#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H

#include <vector>
#include "ProblemPart.h"
using std::cout;
using std::endl;


class Calculator {
public:
    double evaluate(std::string problem);

private:
    bool isAnOperation(char character);

    std::string removeWhiteSpace(std::string problem);

    std::vector<ProblemPart> parseProblem(std::string problem);

};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H
