#pragma once


#include "Mesh.h"
#include "DirichletSolverInterface.h"
#include <fstream>
#include <sstream>

class MshMeshLoader {
public:
    Mesh loadMesh(const std::string &fileName, const DirichletSolverInterface &dirichlet);

    void updateMesh(const std::string &inFileName, const std::string &outFileName, std::vector<Node> nodes);
//    void saveMesh(const Mesh& mesh, const std::string& fileName);
private:
};