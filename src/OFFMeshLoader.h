#pragma once
#include "Mesh.h"
#include "DirichletSolverInterface.h"

class OFFMeshLoader {
public:
    Mesh loadMesh(const std::string& fileName, const DirichletSolverInterface& dirichlet);
    void saveMesh(const Mesh& mesh, const std::string& fileName);
private:
    enum class ElementType {
        TRIANGLE = 3
    };
};
