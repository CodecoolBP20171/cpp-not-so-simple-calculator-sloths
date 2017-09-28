//
// Created by meszi on 2017.09.27..
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PRARSER_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PRARSER_H


#include <vector>
#include <stdexcept>
#include "ProblemPart.h"

class Parser {
public:
    std::vector<ProblemPart> parseProblem(std::string &problem);

private:
    std::string removeWhiteSpace(std::string &problem);

    bool isAValidProblem(std::string &problem);

    std::vector<ProblemPart> generateProblemParts(const std::string &problem);

    bool isANumber(char &character);

    bool isABracket(char &character);

    PartType getOperationType(std::string &substring);

    void addNewNumber(std::vector<ProblemPart> &problemParts, std::string &number);

    void addNewOperation(std::vector<ProblemPart> &problemParts, std::string &operation);

    void addNewBracket(std::vector<ProblemPart> &problemParts, char &character);

    void validateBracket(std::vector<ProblemPart> &problemParts);
};


#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PRARSER_H
