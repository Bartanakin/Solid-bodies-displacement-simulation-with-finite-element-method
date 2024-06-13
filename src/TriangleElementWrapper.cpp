//
// Created by barta on 26/05/2024.
//

#include <iostream>
#include "TriangleElementWrapper.h"

TriangleElementWrapper::TriangleElementWrapper(
    const TriangleElement &triangleElement,
    const std::vector<Node> &nodes
) noexcept :
    triangleElement(triangleElement),
    nodes(nodes)
{}

double TriangleElementWrapper::calcArea() const {
    const auto& e = this->triangleElement;
    auto area= (nodes[e.pointIndices[0]].point[0] - nodes[e.pointIndices[1]].point[0]) * (nodes[e.pointIndices[0]].point[1] - nodes[e.pointIndices[2]].point[1]);
    area -= (nodes[e.pointIndices[0]].point[0] - nodes[e.pointIndices[2]].point[0]) * (nodes[e.pointIndices[0]].point[1] - nodes[e.pointIndices[1]].point[1]);
    area *= .5;

    return area;
}

double TriangleElementWrapper::calcIntegralOfDerivatives(
    unsigned int i,
    unsigned int j,
    unsigned int p,
    unsigned int q
) const {
    const auto& e = this->triangleElement;
    auto result = (p + q) % 2 == 0 ? 1. : -1.;
    result *= nodes[e.pointIndices[(i + 1) % 3]].point[(p + 1) % 2] - nodes[e.pointIndices[(i + 2) % 3]].point[(p + 1) % 2];
    result *= nodes[e.pointIndices[(j + 1) % 3]].point[(q + 1) % 2] - nodes[e.pointIndices[(j + 2) % 3]].point[(q + 1) % 2];
    result *= .5 ;

    auto area= (nodes[e.pointIndices[0]].point[0] - nodes[e.pointIndices[1]].point[0]) * (nodes[e.pointIndices[0]].point[1] - nodes[e.pointIndices[2]].point[1]);
    area -= (nodes[e.pointIndices[0]].point[0] - nodes[e.pointIndices[2]].point[0]) * (nodes[e.pointIndices[0]].point[1] - nodes[e.pointIndices[1]].point[1]);
    result /= area;

    return result;
}

double TriangleElementWrapper::calcIntegralOfElement() const {
    return this->calcArea() / 3.;
}

const TriangleElement& TriangleElementWrapper::getElement() const noexcept {
    return this->triangleElement;
}

double TriangleElementWrapper::calcIntegralOverEdge(unsigned int globalNodeIndex) const {
    const auto& n1 = this->nodes[globalNodeIndex];
    const auto& n2 = this->nodes[this->findNextGlobalIndex(globalNodeIndex)];

    return 0.5 * (n1.point - n2.point).norm();
}

unsigned int TriangleElementWrapper::findLocalNodeIndex(unsigned int globalNodeIndex) const {
    unsigned int i;
    for (i = 0; i < 3; i++) {
        if (triangleElement.pointIndices[i] == globalNodeIndex) {
            return i;
        }
    }

    throw std::runtime_error("Local index not found");
}

unsigned int TriangleElementWrapper::findNextGlobalIndex(unsigned int globalNodeIndex) const {
    return this->triangleElement.pointIndices[(this->findLocalNodeIndex(globalNodeIndex) + 1) % 3];
}
