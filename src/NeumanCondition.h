#pragma once


#include "NeumanConditionInterface.h"
#include "Mesh.h"

class NeumanCondition : public NeumanConditionInterface {
public:
    NeumanCondition(const Mesh& mesh, const std::string& fileName) noexcept;

    bool isNeuman(unsigned int elementIndex) const override;

    /*
     * @inheritDoc
     */
    const NeumanDataContainer& getEdgeIndicesForNeuman(unsigned int elementIndex) const override;
private:
    const Mesh& mesh;
    std::unordered_map<std::string, std::vector<std::pair<unsigned int, Eigen::Vector2d>>> map;
};
