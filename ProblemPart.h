//
// Created by meszi on 2017.09.25..
//

#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H

#include <iostream>
#include "PartType.h"


class ProblemPart {
public:
    ProblemPart(std::string part, PartType  partType=NUMBER);
    std::string getPart() { return part; }
    PartType getPartType() {return partType; }
    void setPartType(PartType partType) { this->partType; }
    std::string print();
private:
    std::string part;
    PartType partType;

};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H
