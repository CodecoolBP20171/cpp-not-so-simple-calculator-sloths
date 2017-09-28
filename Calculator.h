#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H

#include <vector>
#include "ProblemPart.h"
#include "Parser.h"
using std::cout;
using std::endl;


class Calculator {
public:
    double evaluate(std::string problem);

private:
    std::vector<ProblemPart> solveSingleOperation(std::vector<ProblemPart> &problemParts);

    void updateProblemParts(std::vector<ProblemPart> &problemParts, int index, double newNumber) const;

    void solveThirdDegreeOperation(std::vector<ProblemPart> &problemParts);

    void solveSecondDegreeOperation(std::vector<ProblemPart> &problemParts);

    void solveFirstDegreeOperation(std::vector<ProblemPart> &problemParts);

    void solveParentheses(std::vector<ProblemPart> &problemParts);

    bool nextToNumbers(std::vector<ProblemPart> &problemParts, int index);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_CALCUALTOR_H
