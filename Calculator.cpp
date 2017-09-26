#include <cmath>
#include "Calculator.h"


double Calculator::evaluate(std::string problem) {
    problem = removeWhiteSpace(problem);
    std::vector<ProblemPart> problemParts = parseProblem(problem);
    problemParts = solveSingleOperation(problemParts);
    return problemParts[0].getNumber();
}

std::vector<ProblemPart> Calculator::parseProblem(std::string problem) {
    std::vector<ProblemPart> problemParts;
    std::string currentNumber;

    for (int i = 0; i < problem.length(); ++i) {
        char currentCharacter = problem[i];

        if (!isAnOperation(currentCharacter)) {
            currentNumber += currentCharacter;
        }
        else {
            problemParts.push_back(ProblemPart(currentNumber, NUMBER));
            currentNumber = "";

            std::string currentOperation;
            currentOperation += currentCharacter;

            switch (currentCharacter) {
                case '+':
                    problemParts.push_back(ProblemPart(currentOperation, ADDITION));
                    break;
                case '-':
                    problemParts.push_back(ProblemPart(currentOperation, SUBTRACTION));
                    break;
                case '*':
                    problemParts.push_back(ProblemPart(currentOperation, MULTIPLICATION));
                    break;
                case '/':
                    problemParts.push_back(ProblemPart(currentOperation, DIVISION));
                    break;
                case '^':
                    problemParts.push_back(ProblemPart(currentOperation, POWER));
                    break;
                case 'r':
                    if (problem.find("root") == i) {
                        problemParts.push_back(ProblemPart("root", ROOT));
                        i += 3;
                    }
                    break;

            }
        }
    }
    problemParts.push_back(ProblemPart(currentNumber, NUMBER));

    return problemParts;
}

bool Calculator::isAnOperation(char character) {
    if (character == '/' || character == '*' ||
        character == '+' || character == '-' ||
        character == 'r' || character == '^') {
        return true;
    }
    return false;
}

std::string Calculator::removeWhiteSpace(std::string problem) {
    while (problem.find(" ") != std::string::npos) {
        problem.replace(problem.find(" "), 1, "");
    }
    return problem;
}

std::vector<ProblemPart> Calculator::solveSingleOperation(std::vector<ProblemPart> problemParts) {
    int index = 0;
    double newNumber;

    for (ProblemPart part : problemParts) {

        if (part.getPartType() == POWER) {
            newNumber = std::pow(problemParts.at(index - 1).getNumber(), problemParts.at(index + 1).getNumber());
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 2) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        else if (part.getPartType() == ROOT) {
            newNumber = std::pow(problemParts.at(index + 1).getNumber(), 1.0/problemParts.at(index - 1).getNumber());
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 2) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        index++;
    }
    index = 0;

    for (ProblemPart part : problemParts) {

        if (part.getPartType() == DIVISION) {
            newNumber = problemParts.at(index - 1).getNumber() / problemParts.at(index + 1).getNumber();
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 2) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        else if (part.getPartType() == MULTIPLICATION) {
            newNumber = problemParts.at(index - 1).getNumber() * problemParts.at(index + 1).getNumber();
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 2) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        index++;
    }
    index = 0;

    for (ProblemPart part : problemParts) {

        if (part.getPartType() == ADDITION) {
            newNumber = problemParts.at(index - 1).getNumber() + problemParts.at(index + 1).getNumber();
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        else if (part.getPartType() == SUBTRACTION) {
            newNumber = problemParts.at(index - 1).getNumber() - problemParts.at(index + 1).getNumber();
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        index++;
    }
    return  problemParts;
}

void Calculator::updateProblemParts(std::vector<ProblemPart> &problemParts, int index, double newNumber) const {
//    problemParts[index - 1] = ProblemPart(std::to_string(newNumber), NUMBER);
//    problemParts.erase(problemParts.begin() + index + 1);
//    problemParts.erase(problemParts.begin() + index);
    std::vector<ProblemPart>::iterator iterator = problemParts.begin();

    problemParts.at(index -1) = ProblemPart(std::to_string(newNumber), NUMBER);
    problemParts.erase(iterator + index);
    problemParts.erase(iterator + index);
}
