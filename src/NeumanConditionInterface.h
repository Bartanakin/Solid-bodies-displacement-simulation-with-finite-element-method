#pragma once

#include <vector>
#include <Eigen/Dense>

using NeumanDataContainer = std::vector<std::pair<unsigned int, Eigen::Vector2d>>;

class NeumanConditionInterface {
public:
    virtual bool isNeuman(unsigned int elementIndex) const = 0;

    virtual const NeumanDataContainer& getEdgeIndicesForNeuman(unsigned int elementIndex) const = 0;
};