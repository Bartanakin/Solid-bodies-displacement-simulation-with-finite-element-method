//
// Created by barta on 08/06/2024.
//

#include <fstream>
#include <iostream>
#include "NeumanCondition.h"

NeumanCondition::NeumanCondition(
    const Mesh &mesh,
    const std::string& fileName
) noexcept :
    mesh(mesh)
{
    std::ifstream fileHandle;
    fileHandle.open(fileName);

    std::string fileLabel;
    std::getline(fileHandle, fileLabel);
    if (fileLabel != "BARTA_NEUMAN") {
        throw std::runtime_error("Incorrect neuman file");
    }

    std::string line;
    std::stringstream ss;

    std::getline(fileHandle, line);
    ss << line;
    unsigned int elementCount;
    ss >> elementCount;
    for (unsigned int i = 0; i < elementCount; i++) {
        ss.clear();
        std::getline(fileHandle, line);
        ss << line;

        std::string elementLabel;
        unsigned int numberOfEdges;
        ss >> elementLabel >> numberOfEdges;

        NeumanDataContainer edges;
        for (unsigned int j = 0; j < numberOfEdges; j++) {
            ss.clear();
            std::getline(fileHandle, line);
            ss << line;
            unsigned int nodeIndex;
            double x, y;
            ss >> nodeIndex >> x >> y;
            edges.push_back({nodeIndex - 1, {x, y}});
        }

        this->map.insert({elementLabel, std::move(edges)});
    }

    fileHandle.close();
}

bool NeumanCondition::isNeuman(unsigned int elementIndex) const {
    return this->map.contains(this->mesh.getElements()[elementIndex].label);
}

const NeumanDataContainer& NeumanCondition::getEdgeIndicesForNeuman(unsigned int elementIndex) const {
    if (this->isNeuman(elementIndex)) {
        return this->map.at(this->mesh.getElements()[elementIndex].label);
    }

    throw std::runtime_error("This element has no Neuman condition");
}
