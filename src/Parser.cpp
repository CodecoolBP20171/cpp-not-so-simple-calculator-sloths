//
// Created by meszi on 2017.09.27..
//

#include "../headers/Parser.h"

std::vector<ProblemPart> Parser::parseProblem(std::string &problem) {
    problem = removeWhiteSpace(problem);
    if (!isAValidProblem(problem)) {
        throw std::invalid_argument("Problem contains unexpected character(s)!\n");
    }
    std::vector<ProblemPart> problemParts = generateProblemParts(problem);
    if (!(problemParts[0].getType() == NUMBER || problemParts[0].getType() == OPENING_BRACKET)) {
        throw std::invalid_argument("Problem cannot start with an operation!\n");
    }
    validateBracket(problemParts);
    return problemParts;
}

std::vector<ProblemPart> Parser::generateProblemParts(const std::string &problem) {
    std::vector<ProblemPart> problemParts;
    std::string currentNumber;
    std::string currentOperation;

    for (char character : problem) {
        if (isANumber(character)) {
            addNewOperation(problemParts, currentOperation);
            currentNumber += character;
        } else if (isABracket(character)) {
            addNewNumber(problemParts, currentNumber);
            addNewOperation(problemParts, currentOperation);
            addNewBracket(problemParts, character);
        } else {
            addNewNumber(problemParts, currentNumber);
            currentOperation += character;
            if (currentOperation.length() > 4) {
                throw std::invalid_argument("Missing parameter!\n");
            }
        }
    }
    // After iterating through the whole string, there isn't any
    // operators or brackets to trigger saving the last number.
    addNewNumber(problemParts, currentNumber);
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
    std::string validCharacters("0123456789.+-*/^root()");
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

bool Parser::isABracket(char &character) {
    if (character == '(' || character == ')') return true;
    return false;
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

void Parser::addNewBracket(std::vector<ProblemPart> &problemParts, char &character) {
    bool openingBracket = character == '(' ? true : false;
    std::string newPart("");
    if (openingBracket) {
        newPart += character;
        problemParts.push_back(ProblemPart(newPart, OPENING_BRACKET));
    } else {
        int numOfOpeningBrackets = 0;
        int numOfClosingBrackets = 0;

        for (ProblemPart part : problemParts) {
            if (part.getType() == OPENING_BRACKET) {
                ++numOfOpeningBrackets;
                continue;
            } else if (part.getType() == CLOSING_BRACKET) {
                ++numOfClosingBrackets;
            }
        }

        if (numOfOpeningBrackets > numOfClosingBrackets) {
            newPart += character;
            problemParts.push_back(ProblemPart(newPart, CLOSING_BRACKET));
        } else {
            throw std::invalid_argument("Missing opening bracket!\n");
        }
    }
}

void Parser::validateBracket(std::vector<ProblemPart> &problemParts) {
    int numOfOpeningBrackets = 0;
    int numOfClosingBrackets = 0;
    bool previousIsOpening = false;

    for (ProblemPart part : problemParts) {
        if (part.getType() == OPENING_BRACKET) {
            ++numOfOpeningBrackets;
            previousIsOpening = true;
        }else if (part.getType() == CLOSING_BRACKET) {
            ++numOfClosingBrackets;
            if (previousIsOpening) {
                throw std::invalid_argument("Empty bracket!\n");
            }
            previousIsOpening = false;
        } else {
            previousIsOpening = false;
        }
    }

    if (numOfClosingBrackets != numOfOpeningBrackets) {
        throw std::invalid_argument("Missing closing bracket!\n");
    }
}

void Parser::addNewNumber(std::vector<ProblemPart> &problemParts, std::string &number) {
    if (!number.empty()) {
        problemParts.push_back(ProblemPart(number, NUMBER));
        number.clear();
    }
}

void Parser::addNewOperation(std::vector<ProblemPart> &problemParts, std::string &operation) {
    if (!operation.empty()) {
        PartType operationType = getOperationType(operation);
        problemParts.push_back(ProblemPart(operation, operationType));
        operation.clear();
    }
}
