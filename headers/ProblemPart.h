#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H

#include <iostream>
#include "PartType.h"



class ProblemPart {
public:
    ProblemPart(std::string part, PartType  partType);

    PartType getType() { return partType; }

    double getNumber() { return stod(part); }

private:
    std::string part;
    PartType partType;

};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H
