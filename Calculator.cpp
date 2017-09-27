#include <cmath>
#include "Calculator.h"


double Calculator::evaluate(std::string problem) {
    Parser parser;
    std::vector<ProblemPart> problemParts;
    try {
        problemParts = parser.parseProblem(problem);
    } catch (const std::invalid_argument &exception) {
        cout << exception.what() << problem << endl;
        return 0;
    }
    problemParts = solveSingleOperation(problemParts);
    return problemParts[0].getNumber();
}

std::vector<ProblemPart> Calculator::solveSingleOperation(std::vector<ProblemPart> &problemParts) {
    solveParentheses(problemParts);
    solveThirdDegreeOperation(problemParts);
    solveSecondDegreeOperation(problemParts);
    solveFirstDegreeOperation(problemParts);
    return  problemParts;
}

void Calculator::solveFirstDegreeOperation(std::vector<ProblemPart> &problemParts) {
    int index = 0;
    double newNumber;
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
}

void Calculator::solveSecondDegreeOperation(std::vector<ProblemPart> &problemParts) {
    int index = 0;
    double newNumber;
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
}

void Calculator::solveThirdDegreeOperation(std::vector<ProblemPart> &problemParts) {
    int index = 0;
    double newNumber;
    for (ProblemPart part : problemParts) {

        if (part.getPartType() == POWER) {
            newNumber = pow(problemParts.at(index - 1).getNumber(), problemParts.at(index + 1).getNumber());
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 2) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        else if (part.getPartType() == ROOT) {
            newNumber = pow(problemParts.at(index + 1).getNumber(), 1.0/problemParts.at(index - 1).getNumber());
            updateProblemParts(problemParts, index, newNumber);
            if (problemParts.size() > 2) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        index++;
    }
}

void Calculator::updateProblemParts(std::vector<ProblemPart> &problemParts, int index, double newNumber) const {
    std::vector<ProblemPart>::iterator iterator = problemParts.begin();

    problemParts.at(index -1) = ProblemPart(std::to_string(newNumber), NUMBER);
    problemParts.erase(iterator + index);
    problemParts.erase(iterator + index);
}

void Calculator::solveParentheses(std::vector<ProblemPart> &problemParts) {
    int openingIndex = -1;
    int closingIndex = -1;
    int numberOfBrackets = 0;

    for (int i = 0; i < problemParts.size(); i++) {
        if (problemParts[i].getPartType() == OPENING_BRACKET) {
            ++numberOfBrackets;
            if (openingIndex == -1) {
                openingIndex = i;
            }
        } else if (problemParts[i].getPartType() == CLOSING_BRACKET) {
            numberOfBrackets--;

            if (numberOfBrackets == 0) {
                closingIndex = i;
                std::vector<ProblemPart> childrenParts;
                for (int j = openingIndex + 1; j < closingIndex; j++) {
                    childrenParts.push_back(problemParts[j]);
                }
                childrenParts = solveSingleOperation(childrenParts);

                std::vector<ProblemPart>::iterator iterator = problemParts.begin();
                for (int j = 0; j < closingIndex - openingIndex; j++) {
                    problemParts.erase(iterator + openingIndex);
                }
                problemParts.insert(iterator + openingIndex, childrenParts[0]);
                break;
            }
        }
    }
}
