//
// Created by barta on 26/05/2024.
//

#include "Mesh.h"

Mesh::Mesh(
    std::vector<TriangleElement> elements,
    std::vector<Node> nodes
) noexcept :
    elements(std::move(elements)),
    nodes(std::move(nodes))
{}

TriangleElementWrapper Mesh::getWrappedElement(unsigned int index) {
    return {this->elements[index], this->nodes};
}

unsigned int Mesh::getElementCount() const noexcept {
    return this->elements.size();
}

const std::vector<Node> &Mesh::getNodes() const noexcept {
    return this->nodes;
}

const std::vector<TriangleElement> &Mesh::getElements() const noexcept {
    return this->elements;
}
