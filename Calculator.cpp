//
// Created by meszi on 2017.09.25..
//

#include "Calculator.h"


double Calculator::evaluate(std::string problem) {
    std::vector<ProblemPart> problemParts;
    std::string currentNumber = "";
    for (int i = 0; i < problem.length(); ++i) {
        if (!isAnOperation(problem[i])) {
            currentNumber += problem[i];
        }
        else {
            problemParts.push_back(ProblemPart(currentNumber, NUMBER));
            currentNumber = "";
            ProblemPart currentOperation(std::to_string(problem[i]));
            switch (problem[i]) {
                case '+':
                    currentOperation.setPartType(ADDITION);
                    break;
                case '-':
                    currentOperation.setPartType(SUBTRACTION);
                    break;
                case '*':
                    currentOperation.setPartType(MULTIPLICATION);
                    break;
                case '/':
                    currentOperation.setPartType(DIVISION);
                    break;

            }
            problemParts.push_back(currentOperation);
        }
    }
    cout << problemParts.size() << endl;

}

bool Calculator::isAnOperation(char character) {
    if (character == '/' || character == '*' || character == '+' || character == '-')
        return true;
    return false;
}
