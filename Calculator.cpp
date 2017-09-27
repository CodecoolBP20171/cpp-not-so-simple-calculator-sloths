#include <cmath>
#include "Calculator.h"


double Calculator::evaluate(std::string problem) {
    Parser parser;
    std::vector<ProblemPart> problemParts;
    try {
        problemParts = parser.parseProblem(problem);
    } catch (const std::invalid_argument &exception) {
        cout << exception.what() << endl;
        return 0;
    }
    problemParts = solveSingleOperation(problemParts);
    return problemParts[0].getNumber();
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
    std::vector<ProblemPart>::iterator iterator = problemParts.begin();

    problemParts.at(index -1) = ProblemPart(std::to_string(newNumber), NUMBER);
    problemParts.erase(iterator + index);
    problemParts.erase(iterator + index);
}
