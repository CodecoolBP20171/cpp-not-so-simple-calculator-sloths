//
// Created by meszi on 2017.09.27..
//

#include "Parser.h"

std::vector<ProblemPart> Parser::parseProblem(std::string &problem) {
    problem = removeWhiteSpace(problem);
    if (!isAValidProblem(problem)) {
        throw std::invalid_argument("Problem contains unexpected character(s)!\n" + problem);
    }
    return generateProblemParts(problem);
}

std::vector<ProblemPart> Parser::generateProblemParts(const std::string &problem) {
    std::vector<ProblemPart> problemParts;

    bool checkingForNumber = true;
    std::string substring;
    for (char character : problem) {
        if (checkingForNumber) {
            if (isANumber(character)) {
                substring += character;
            } else {
                problemParts.push_back(ProblemPart(substring, NUMBER));
                substring = "";
                checkingForNumber = false;
            }
        }
        if (!checkingForNumber) {
            if (!isANumber(character)) {
                substring += character;
            } else {
                PartType operationType = getOperationType(substring);
                problemParts.push_back(ProblemPart(substring, operationType));
                substring = character;
                checkingForNumber = true;
            }
        }
    }
    problemParts.push_back(ProblemPart(substring, NUMBER));

    return problemParts;
}

std::string Parser::removeWhiteSpace(std::string &problem) {
    std::string whiteSpaces[] = {" ", "\n", "\t", "\f", "\r", "\v"};
    for (std::string whiteSpace : whiteSpaces) {
        while (problem.find(whiteSpace) != std::string::npos) {
            problem.replace(problem.find(whiteSpace), whiteSpace.length(), "");
        }
    }
    return problem;
}

bool Parser::isAValidProblem(std::string &problem) {
    std::string validCharacters("0123456789.+-*/^root");
    for (char character : problem) {
        if (validCharacters.find(character) == std::string::npos) {
            return false;
        }
    }
    return true;
}

bool Parser::isANumber(char &character) {
    std::string validNumberCharacters(".0123456789");
    if (validNumberCharacters.find(character) == std::string::npos) {
        return false;
    }
    return true;
}

PartType Parser::getOperationType(std::string &substring) {
    switch (substring[0]) {
        case '+':
            return ADDITION;
        case '-':
            return SUBTRACTION;
        case '*':
            return MULTIPLICATION;
        case '/':
            return DIVISION;
        case '^':
            return POWER;
        default:
            return ROOT;
    }
}
