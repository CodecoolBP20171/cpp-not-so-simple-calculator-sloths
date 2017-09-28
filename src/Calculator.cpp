#include <cmath>
#include "../headers/Calculator.h"


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
    int idx = 0;
    double newNumber;
    for (ProblemPart part : problemParts) {

        if (part.getType() == ADDITION) {
            newNumber = problemParts[idx-1].getNumber() + problemParts[idx+1].getNumber();
            updateProblemParts(problemParts, idx, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        } else if (part.getType() == SUBTRACTION) {
            newNumber = problemParts[idx-1].getNumber() - problemParts[idx+1].getNumber();
            updateProblemParts(problemParts, idx, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        idx++;
    }
}

void Calculator::solveSecondDegreeOperation(std::vector<ProblemPart> &problemParts) {
    int idx = 0;
    double newNumber;
    for (ProblemPart part : problemParts) {

        if (part.getType() == DIVISION) {
            newNumber = problemParts[idx-1].getNumber() / problemParts[idx+1].getNumber();
            updateProblemParts(problemParts, idx, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        } else if (part.getType() == MULTIPLICATION) {
            newNumber = problemParts[idx-1].getNumber() * problemParts[idx+1].getNumber();
            updateProblemParts(problemParts, idx, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        idx++;
    }
}

void Calculator::solveThirdDegreeOperation(std::vector<ProblemPart> &problemParts) {
    int idx = 0;
    double newNumber;
    for (ProblemPart part : problemParts) {

        if (part.getType() == POWER) {
            newNumber = pow(problemParts[idx-1].getNumber(), problemParts[idx+1].getNumber());
            updateProblemParts(problemParts, idx, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        } else if (part.getType() == ROOT) {
            newNumber = pow(problemParts[idx+1].getNumber(), 1.0/problemParts[idx-1].getNumber());
            updateProblemParts(problemParts, idx, newNumber);
            if (problemParts.size() > 1) {
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
        idx++;
    }
}

void Calculator::solveParentheses(std::vector<ProblemPart> &problemParts) {
    int openingIndex = -1;
    int closingIndex = -1;
    int numberOfBrackets = 0;

    for (int i = 0; i < problemParts.size(); ++i) {
        if (problemParts[i].getType() == OPENING_BRACKET) {
            ++numberOfBrackets;
            if (openingIndex == -1) {
                openingIndex = i;
            }
        } else if (problemParts[i].getType() == CLOSING_BRACKET) {
            numberOfBrackets--;

            if (numberOfBrackets == 0) {
                closingIndex = i;
                std::vector<ProblemPart> childrenParts;
                for (int j = openingIndex + 1; j < closingIndex; ++j) {
                    childrenParts.push_back(problemParts[j]);
                }
                childrenParts = solveSingleOperation(childrenParts);

                std::vector<ProblemPart>::iterator iterator = problemParts.begin();
                for (int j = 0; j < closingIndex - openingIndex + 1; ++j) {
                    problemParts.erase(iterator + openingIndex);
                }
                problemParts.insert(iterator + openingIndex, childrenParts[0]);
                problemParts = solveSingleOperation(problemParts);
                break;
            }
        }
    }
}

void Calculator::updateProblemParts(std::vector<ProblemPart> &problemParts, int index, double newNumber) const {
    std::vector<ProblemPart>::iterator iterator = problemParts.begin();

    problemParts.at(index -1) = ProblemPart(std::to_string(newNumber), NUMBER);
    problemParts.erase(iterator + index);
    problemParts.erase(iterator + index);
}
