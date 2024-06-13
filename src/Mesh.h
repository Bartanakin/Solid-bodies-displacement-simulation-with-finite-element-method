#pragma once
#include "TriangleElementWrapper.h"
#include <vector>

class Mesh {
public:
    Mesh(
        std::vector<TriangleElement> elements,
        std::vector<Node> nodes
    ) noexcept;

    TriangleElementWrapper getWrappedElement(unsigned int index);

    const std::vector<TriangleElement>& getElements() const noexcept;

    unsigned int getElementCount() const noexcept;

    const std::vector<Node>& getNodes() const noexcept;
private:
    std::vector<TriangleElement> elements;
    std::vector<Node> nodes;
};
