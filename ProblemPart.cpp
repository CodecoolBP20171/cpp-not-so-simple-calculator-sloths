#include "ProblemPart.h"

ProblemPart::ProblemPart(std::string part, PartType  partType) {
    this->part = part;
    this->partType = partType;
}

void ProblemPart::print() {
    std::cout << part << std::endl;
}
