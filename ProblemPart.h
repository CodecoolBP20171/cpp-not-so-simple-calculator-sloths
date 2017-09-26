#ifndef CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H
#define CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H

#include <iostream>
#include "PartType.h"



class ProblemPart {
public:
    ProblemPart(std::string part, PartType  partType);

    std::string getPart() { return part; }

    PartType getPartType() {return partType; }

    double getNumber() { return atof(part.c_str()); }
    void setPartType(PartType partType) { this->partType; }

    void print();
private:
    std::string part;
    PartType partType;

};

#endif //CPP_NOT_SO_SIMPLE_CALCULATOR_SLOTHS_PROBLEMPART_H
