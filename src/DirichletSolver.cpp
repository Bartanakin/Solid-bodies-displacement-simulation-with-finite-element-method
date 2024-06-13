//
// Created by barta on 03/06/2024.
//

#include <fstream>
#include "DirichletSolver.h"

DirichletSolver::DirichletSolver(const std::string& filename) {
    std::ifstream fileHandle;
    fileHandle.open(filename);
    if (!fileHandle.is_open()) {
        std::runtime_error("File not found");
    }

    std::string fileLabel;
    std::getline(fileHandle, fileLabel);
    if (fileLabel != "BARTA_DIRICHLET") {
        throw std::runtime_error("Incorrect dirichlet file");
    }

    std::string line;
    std::getline(fileHandle, line);
    std::stringstream ss;
    ss << line;
    unsigned int nodeCount;
    ss >> nodeCount;
    for (int i = 0; i < nodeCount; i++) {
        std::getline(fileHandle, line);
        std::stringstream ss;
        ss << line;
        unsigned int nodeIndex;
        ss >> nodeIndex;

        this->dirichletNodes.insert({nodeIndex - 1, true});
    }

    fileHandle.close();
}

bool DirichletSolver::isDirichlet(Eigen::Vector2d node, unsigned int nodeIndex) const {
    return this->dirichletNodes.contains(nodeIndex);
}
