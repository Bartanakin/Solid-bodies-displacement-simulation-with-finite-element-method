//
// Created by barta on 08/06/2024.
//

#include <iostream>
#include "MshMeshLoader.h"

Mesh MshMeshLoader::loadMesh(const std::string &fileName, const DirichletSolverInterface &dirichlet) {

    std::ifstream inputHandle;
    inputHandle.open(fileName);
    if (!inputHandle.is_open()) {
        throw std::runtime_error("File not found");
    }

    std::string line;
    std::vector<Node> nodes;
    std::vector<TriangleElement> triangleElements;
    do {
        std::getline(inputHandle, line);
        if (line == "$Nodes") {
            std::getline(inputHandle, line);
            std::stringstream ss;
            ss << line;
            size_t nodeCount;
            ss >> line >> nodeCount >> line >> line;

            nodes.reserve(nodeCount);
            size_t nodesForward;
            for (int i = 0; i < nodeCount; i += nodesForward) {
                std::getline(inputHandle, line);
                ss.clear();
                ss << line;
                ss >> line >> line >> line >> nodesForward;
                for (int j = i; j < i + nodesForward; j++) {
                    std::getline(inputHandle, line);
                }

                for (int j = i; j < i + nodesForward; j++) {
                    std::getline(inputHandle, line);
                    double x, y, z;
                    ss.clear();
                    ss << line;
                    ss >> x >> y >> z;
                    auto point = Eigen::Vector2d(x, y);
                    nodes.emplace_back(point, dirichlet.isDirichlet(point, j));
                }
            }
        }

        if (line == "$Elements") {
            std::getline(inputHandle, line);
            std::stringstream ss;
            ss << line;
            size_t elementCount;

            ss >> line >> elementCount >> line >> line;
            triangleElements.reserve(elementCount);

            size_t nodesForward = 0;
            for (int i = 0; i < elementCount; i += nodesForward) {
                unsigned int dimension;
                std::getline(inputHandle, line);
                ss.clear();
                ss << line;
                ss >> dimension >> line >> line >> nodesForward;
                for (int j = i; j < i + nodesForward; j++) {
                    std::getline(inputHandle, line);

                    // if triangle
                    if (dimension == 2) {
                        ss.clear();
                        ss << line;

                        std::string label;
                        unsigned int n1, n2, n3;
                        ss >> label >> n1 >> n2 >> n3;
                        triangleElements.emplace_back(n1 - 1, n2 - 1, n3 - 1, label);
                    }
                }
            }
        }
    } while (!line.empty());

    inputHandle.close();

    return {std::move(triangleElements), std::move(nodes)};
}

void MshMeshLoader::updateMesh(const std::string &inFileName, const std::string &outFileName, std::vector<Node> nodes) {
    auto inputHandle = std::ifstream(inFileName);
    auto outputHandle = std::ofstream (outFileName);
    std::string line;
    do {
        std::getline(inputHandle, line);
        outputHandle << line << std::endl;
        if (line == "$Nodes") {
            std::getline(inputHandle, line);
            outputHandle << line << std::endl;;
            std::stringstream ss;
            ss << line;
            size_t nodeCount;
            ss >> line >> nodeCount >> line >> line;
            if (nodeCount != nodes.size()) {
                throw std::runtime_error("node count doesn't match");
            }

            size_t nodesForward;
            for (int i = 0; i < nodeCount; i += nodesForward) {
                std::getline(inputHandle, line);
                outputHandle << line << std::endl;
                ss.clear();
                ss << line;
                ss >> line >> line >> line >> nodesForward;
                for (int j = i; j < i + nodesForward; j++) {
                    std::getline(inputHandle, line);
                    outputHandle << line << std::endl;
                }

                for (int j = i; j < i + nodesForward; j++) {
                    std::getline(inputHandle, line);
                    outputHandle << nodes[j].point[0] << " " << nodes[j].point[1] << " " << 0 << std::endl;
                }
            }
        }
    } while (!line.empty());

    inputHandle.close();
    outputHandle.close();
}
