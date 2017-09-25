//
// Created by meszi on 2017.09.25..
//

#include "ProblemPart.h"

ProblemPart::ProblemPart(std::string part, PartType  partType) {
    this->part = part;
    this->partType = partType;
}

std::string ProblemPart::print() {
    return part;
}
