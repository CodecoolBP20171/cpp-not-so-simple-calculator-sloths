#include "Calculator.h"


double Calculator::evaluate(std::string problem) {
    problem = removeWhiteSpace(problem);
    std::vector<ProblemPart> problemParts = parseProblem(problem);

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
    return problem;
}
