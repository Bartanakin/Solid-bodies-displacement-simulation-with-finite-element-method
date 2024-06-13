#pragma once
#include <Eigen/Dense>

class Node {
public:
    Node(
        Eigen::Vector2d point,
        bool isDirichlet = false
    ) noexcept;

    Eigen::Vector2d point;
    bool isDirichlet;
};
