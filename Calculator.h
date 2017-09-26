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

    std::vector<ProblemPart> solveSingleOperation(std::vector<ProblemPart> problemParts);

    void updateProblemParts(std::vector<ProblemPart> &problemParts, int index, double newNumber) const;
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H
