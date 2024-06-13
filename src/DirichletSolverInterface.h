#pragma once


#include "Eigen/Core"

class DirichletSolverInterface {
public:
    virtual bool isDirichlet(Eigen::Vector2d node, unsigned int nodeIndex) const = 0;
};
