//
// Created by meszi on 2017.09.27..
//

#include "Parser.h"

std::vector<ProblemPart> Parser::parseProblem(std::string &problem) {
    problem = removeWhiteSpace(problem);
    if (!isAValidProblem(problem)) {
        throw std::invalid_argument("Problem contains unexpected character(s)!\n");
    }
    std::vector<ProblemPart> problemParts = generateProblemParts(problem);
    validateBracket(problemParts);
    return problemParts;
}

std::vector<ProblemPart> Parser::generateProblemParts(const std::string &problem) {
    std::vector<ProblemPart> problemParts;
    std::string currentNumber;
    std::string currentOperation;

    for (char character : problem) {
        if (isANumber(character)) {
            if (!currentOperation.empty()) {
                PartType operationType = getOperationType(currentOperation);
                problemParts.push_back(ProblemPart(currentOperation, operationType));
                currentOperation.clear();
            }
            currentNumber += character;
        } else if (isABracket(character)) {
            if (!currentNumber.empty()) {
                problemParts.push_back(ProblemPart(currentNumber, NUMBER));
                currentNumber.clear();
            }
            if (!currentOperation.empty()) {
                PartType operationType = getOperationType(currentOperation);
                problemParts.push_back(ProblemPart(currentOperation, operationType));
                currentOperation.clear();
            }
            problemParts.push_back(parseBracket(problemParts, character));
        } else {
            if (!currentNumber.empty()) {
                problemParts.push_back(ProblemPart(currentNumber, NUMBER));
                currentNumber.clear();
            }
            currentOperation += character;
            if (currentOperation.length() > 4) {
                throw std::invalid_argument("Missing parameter!\n");
            }
        }
    }
    if (!currentNumber.empty()) {
        problemParts.push_back(ProblemPart(currentNumber, NUMBER));
        currentNumber.clear();
    }

//    bool checkingForNumber = false;
//    std::string substring;
//    for (char character : problem) {
//        if (checkingForNumber) {
//            if (isANumber(character)) {
//                substring += character;
//            } else {
//                problemParts.push_back(ProblemPart(substring, NUMBER));
//                substring = "";
//                checkingForNumber = false;
//            }
//        }
//        if (!checkingForNumber) {
//            if (!isANumber(character)) {
//                if (isABracket(character)) {
//                    if (isANumber(substring[0])) {
//                        problemParts.push_back(ProblemPart(substring, NUMBER));
//                    } else {
//                        PartType operationType = getOperationType(substring);
//                        problemParts.push_back(ProblemPart(substring, operationType));
//                    }
//                    substring = "";
//                    problemParts.push_back(parseBracket(problemParts, character));
//                } else {
//                    substring += character;
//                }
//            } else {
//                PartType operationType = getOperationType(substring);
//                problemParts.push_back(ProblemPart(substring, operationType));
//                substring = character;
//                checkingForNumber = true;
//            }
//        }
//    }
//    problemParts.push_back(ProblemPart(substring, NUMBER));

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

bool Parser::isABracket(char &character) {
    if (character == '(' || character == ')') {
        return true;
    }
    return false;
}

ProblemPart Parser::parseBracket(std::vector<ProblemPart> &problemParts, char &character) {
    bool openingBracket = character == '(' ? true : false;
    std::string newPart("");
    if (openingBracket) {
        newPart += character;
        return ProblemPart(newPart, OPENING_BRACKET);
    } else {
        int numOfOpeningBrackets = 0;
        int numOfClosingBrackets = 0;

        for (ProblemPart part : problemParts) {
            if (part.getPartType() == OPENING_BRACKET) {
                ++numOfOpeningBrackets;
                continue;
            } else if (part.getPartType() == CLOSING_BRACKET) {
                ++numOfClosingBrackets;
            }
        }

        if (numOfOpeningBrackets > numOfClosingBrackets) {
            newPart += character;
            return ProblemPart(newPart, CLOSING_BRACKET);
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
        if (part.getPartType() == OPENING_BRACKET) {
            ++numOfOpeningBrackets;
            previousIsOpening = true;
        }else if (part.getPartType() == CLOSING_BRACKET) {
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
