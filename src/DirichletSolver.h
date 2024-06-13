#pragma once


#include "DirichletSolverInterface.h"

class DirichletSolver : public DirichletSolverInterface {
public:
    DirichletSolver(const std::string& filename);

    bool isDirichlet(Eigen::Vector2d node, unsigned int nodeIndex) const override;
private:
    std::unordered_map<unsigned int, bool> dirichletNodes;
};
