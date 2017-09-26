#include "ProblemPart.h"

ProblemPart::ProblemPart(std::string part, PartType  partType) {
    this->part = part;
    this->partType = partType;
}

std::string ProblemPart::print() {
    return part;
}
