//
// Created by barta on 22/05/2024.
//

#include "Node.h"

Node::Node(Eigen::Vector2d point, bool isDirichlet) noexcept :
    point(std::move(point)),
    isDirichlet(isDirichlet)
{}
