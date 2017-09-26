#include "Calculator.h"


double Calculator::evaluate(std::string problem) {
    problem = removeWhiteSpace(problem);
    std::vector<ProblemPart> problemParts = parseProblem(problem);
    problemParts = solveSingleOperation(problemParts);
    for (ProblemPart part : problemParts) {
        part.print();
    }
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

            }
        }
    }
    problemParts.push_back(ProblemPart(currentNumber, NUMBER));

    return problemParts;
}

bool Calculator::isAnOperation(char character) {
    if (character == '/' || character == '*' || character == '+' || character == '-')
        return true;
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

        if (part.getPartType() == DIVISION) {
            newNumber = problemParts.at(index - 1).getNumber() / problemParts.at(index + 1).getNumber();
            problemParts[index -1] = ProblemPart(std::to_string(newNumber), NUMBER);
            problemParts.erase(problemParts.begin() + index + 1);
            problemParts.erase(problemParts.begin() + index);
            problemParts = solveSingleOperation(problemParts);
        }
        else if (part.getPartType() == MULTIPLICATION) {
            newNumber = problemParts.at(index - 1).getNumber() * problemParts.at(index + 1).getNumber();
            problemParts[index -1] = ProblemPart(std::to_string(newNumber), NUMBER);
            problemParts.erase(problemParts.begin() + index + 1);
            problemParts.erase(problemParts.begin() + index);
            problemParts = solveSingleOperation(problemParts);
        }
        index++;
    }
    index = 0;
    for (ProblemPart part : problemParts) {

        if (part.getPartType() == ADDITION) {
            newNumber = problemParts.at(index - 1).getNumber() + problemParts.at(index + 1).getNumber();
            problemParts[index -1] = ProblemPart(std::to_string(newNumber), NUMBER);
            problemParts.erase(problemParts.begin() + index + 1);
            problemParts.erase(problemParts.begin() + index);
            problemParts = solveSingleOperation(problemParts);
        }
        else if (part.getPartType() == SUBTRACTION) {
            newNumber = problemParts.at(index - 1).getNumber() - problemParts.at(index + 1).getNumber();
            problemParts[index -1] = ProblemPart(std::to_string(newNumber), NUMBER);
            problemParts.erase(problemParts.begin() + index + 1);
            problemParts.erase(problemParts.begin() + index);
            problemParts = solveSingleOperation(problemParts);
        }
        index++;
    }
    return  problemParts;
}
