//
// Created by barta on 26/05/2024.
//

#include "OFFMeshLoader.h"
#include <fstream>

Mesh OFFMeshLoader::loadMesh(const std::string &fileName, const DirichletSolverInterface &dirichlet) {
    std::ifstream fileHandle;
    fileHandle.open(fileName);
    if (!fileHandle.is_open()) {
        throw std::runtime_error("File not fount");
    }

    std::string offFlag;
    fileHandle >> offFlag;
    if (offFlag != "OFF") {
        throw std::runtime_error("OFF flag not found");
    }

    unsigned int nodeCount;
    unsigned int elementCount;
    unsigned int volumesCount;
    fileHandle >> nodeCount >> elementCount >> volumesCount;
    std::vector<Node> nodes;
    std::vector<TriangleElement> triangleElements;
    nodes.reserve(nodeCount);
    triangleElements.reserve(elementCount);
    for (int i = 0; i < nodeCount; i++) {
        double x, y, z;
        fileHandle >> x;
        fileHandle >> y;
        fileHandle >> z;

        auto position = Eigen::Vector2d(x, y);

        nodes.emplace_back(position, dirichlet.isDirichlet(position, i));
    }

    for (int i = 0; i < elementCount; i++) {
        unsigned int type;
        fileHandle >> type;
        if (type != static_cast<unsigned int>(ElementType::TRIANGLE)) {
            throw std::runtime_error("Element type not supported.");
        }

        unsigned int indices[3];
        for (unsigned int & index : indices) {
            fileHandle >> index;
        }

        triangleElements.emplace_back(indices);
    }

    fileHandle.close();

    return {std::move(triangleElements), std::move(nodes)};
}

void OFFMeshLoader::saveMesh(const Mesh &mesh, const std::string &fileName) {
    std::ofstream fileHandle(fileName);
    fileHandle << "OFF" << " " << mesh.getNodes().size() << " " << mesh.getElementCount() << " " << 0 << "\n" ;
    for (const auto& node : mesh.getNodes()) {
        fileHandle << node.point[0] << " " << node.point[1] << " " << 0 << "\n";
    }

    for (const auto& element : mesh.getElements()) {
        fileHandle
            << static_cast<unsigned int>(ElementType::TRIANGLE)
            << " "
            << element.pointIndices[0]
            << " "
            << element.pointIndices[1]
            << " "
            << element.pointIndices[2]
            << "\n";
    }

    fileHandle.close();
}
