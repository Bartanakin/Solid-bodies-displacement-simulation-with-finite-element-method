#pragma once
#include "TriangleElement.h"
#include "Node.h"

class TriangleElementWrapper {
public:
    TriangleElementWrapper(
        const TriangleElement& triangleElement,
        const std::vector<Node>& nodes
    ) noexcept;

    double calcArea() const;

    /**
     * @param i index of the first base function
     * @param j index of the second base function
     * @param p index of the first partial derivative
     * @param q index of the second partial derivative
     */
    double calcIntegralOfDerivatives(unsigned int i, unsigned int j, unsigned int p, unsigned int q) const;

    double calcIntegralOfElement() const;

    /**
     * @param globalNodeIndex indicates which edge to be used -> to get the edge you need to take the next vertex counterclockwise
     */
    double calcIntegralOverEdge(unsigned int globalNodeIndex) const;

    const TriangleElement& getElement() const noexcept;

    unsigned int findLocalNodeIndex(unsigned int globalNodeIndex) const;

    unsigned int findNextGlobalIndex(unsigned int globalNodeIndex) const;

private:
    const TriangleElement& triangleElement;
    const std::vector<Node>& nodes;
};
