#pragma once
#include <Eigen/SparseCore>
#include <Eigen/SparseCholesky>
#include <algorithm>
#include "Node.h"


class TriangleElement {
public:
    TriangleElement(
        unsigned int pointIndex0,
        unsigned int pointIndex1,
        unsigned int pointIndex2,
        std::string label = ""
    ) noexcept;

    TriangleElement(
        unsigned int* indices
    ) noexcept;


    std::string label;
    unsigned int pointIndices[3];

    std::string to_string() const;
};
