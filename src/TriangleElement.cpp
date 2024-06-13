//
// Created by barta on 21/05/2024.
//

#include "TriangleElement.h"
#include <sstream>

TriangleElement::TriangleElement(
    unsigned int pointIndex0,
    unsigned int pointIndex1,
    unsigned int pointIndex2,
    std::string label
) noexcept :
    label(label)
{
    this->pointIndices[0] = pointIndex0;
    this->pointIndices[1] = pointIndex1;
    this->pointIndices[2] = pointIndex2;
}

std::string TriangleElement::to_string() const {
    std::stringstream ss;
    ss << "(" << this->pointIndices[0] << " " << this->pointIndices[1] << " " << this->pointIndices[2] << ")";

    return ss.str();
}

TriangleElement::TriangleElement(
    unsigned int *indices
) noexcept {
    std::copy(indices, indices + 3, this->pointIndices);
}
