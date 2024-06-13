#include <iostream>
#include <filesystem>
#include <vector>
#include "TriangleElement.h"
#include "DirichletSolver.h"
#include "MshMeshLoader.h"
#include "NeumanCondition.h"
#include <Eigen/SparseCholesky>

int main(int argc, char **argv) {

    std::ifstream parametersFile;
    parametersFile.open(argv[4]);
    if (!parametersFile.is_open()) {
        throw std::runtime_error("parameters file not found");
    }

    double E; // N / m^2
    double nee; // no unit
    double DENSITY; // kg / m^3
    double GRAVITY; // m * kg / s^2
    parametersFile >> E >> nee >> DENSITY >> GRAVITY;

    parametersFile.close();

    double alpha = E / ((1 - nee * nee)); // N / m^2
    double one_minus_nee_over_two = (1. - nee) / 2.; // N / m^2

    auto mesh = MshMeshLoader().loadMesh(argv[1], DirichletSolver(argv[2]));
    auto neuman = NeumanCondition(mesh, argv[3]);


    Eigen::VectorXd nodalForces = Eigen::VectorXd ::Zero(2 * mesh.getNodes().size());
    std::vector<Eigen::Triplet<double>> tripletList;
    tripletList.reserve(4 * 3 * 3 * mesh.getElementCount());
    for (unsigned int e_index = 0; e_index < mesh.getElementCount(); e_index++) {
        const auto& elementWrapper = mesh.getWrappedElement(e_index);
        const auto& e = elementWrapper.getElement();
        for (unsigned int j = 0; j < 3; j++) {
            if (mesh.getNodes()[e.pointIndices[j]].isDirichlet) {
                continue;
            }

            for (unsigned int i = 0; i < 3; i++) {
                tripletList.emplace_back(
                    2 * e.pointIndices[j],
                    2 * e.pointIndices[i],
                    elementWrapper.calcIntegralOfDerivatives(j, i, 0, 0)
                        + one_minus_nee_over_two * elementWrapper.calcIntegralOfDerivatives(j, i, 1, 1)
                );
                tripletList.emplace_back(
                    2 * e.pointIndices[j],
                    2 * e.pointIndices[i] + 1,
                    nee * elementWrapper.calcIntegralOfDerivatives(j, i, 0, 1)
                       + one_minus_nee_over_two * elementWrapper.calcIntegralOfDerivatives(j, i, 1, 0)
                );

                tripletList.emplace_back(
                    2 * e.pointIndices[j] + 1,
                    2 * e.pointIndices[i] + 1,
                    elementWrapper.calcIntegralOfDerivatives(j, i, 1, 1)
                       + one_minus_nee_over_two * elementWrapper.calcIntegralOfDerivatives(j, i, 0, 0)
                );
                tripletList.emplace_back(
                    2 * e.pointIndices[j] + 1,
                    2 * e.pointIndices[i],
                    nee * elementWrapper.calcIntegralOfDerivatives(j, i, 1, 0)
                        + one_minus_nee_over_two * elementWrapper.calcIntegralOfDerivatives(j, i, 0, 1)
                );
            }

            nodalForces[2 * e.pointIndices[j] + 1] += DENSITY * GRAVITY * elementWrapper.calcIntegralOfElement();
        }

        if (neuman.isNeuman(e_index)) {
            const auto& e = mesh.getWrappedElement(e_index);
            for (auto edgeData : neuman.getEdgeIndicesForNeuman(e_index)) {
                Eigen::Vector2d value = e.calcIntegralOverEdge(edgeData.first) * edgeData.second;
                auto secondNode = e.findNextGlobalIndex(edgeData.first);

                Eigen::Vector2d normal = mesh.getNodes()[secondNode].point - mesh.getNodes()[edgeData.first].point;
                normal = Eigen::Vector2d(normal[1], -normal[0]);
                normal.normalize();

                value = {normal[0] * value[0], normal[1] * value[1]};

                nodalForces[2 * edgeData.first] += value[0];
                nodalForces[2 * edgeData.first + 1] += value[1];

                nodalForces[2 * secondNode] += value[0];
                nodalForces[2 * secondNode + 1] += value[1];
            }
        }
    }

    for (unsigned int j = 0; j < mesh.getNodes().size(); j++) {
        if (mesh.getNodes()[j].isDirichlet) {
            tripletList.emplace_back(2 * j,2 * j,1.);
            tripletList.emplace_back(2 * j + 1, 2 * j + 1,1.);
        }
    }

    auto stiffnessMatrix = Eigen::SparseMatrix<double>(2 * mesh.getNodes().size(), 2 * mesh.getNodes().size());
    stiffnessMatrix.setFromTriplets(tripletList.begin(), tripletList.end());

    Eigen::SimplicialCholesky<Eigen::SparseMatrix<double>> chol(stiffnessMatrix);
    Eigen::VectorX<double> translation = chol.solve(nodalForces) / alpha;

//    std::cout << stiffnessMatrix << std::endl;
//    std::cout << nodalForces << std::endl;

    std::vector<Node> updatedNodes;
    updatedNodes.reserve(mesh.getNodes().size());
    for (int i = 0; i < mesh.getNodes().size(); i++) {
        updatedNodes.emplace_back(mesh.getNodes()[i].point + Eigen::Vector2d(translation[2 * i], translation[2 * i + 1]), false);
    }

    MshMeshLoader().updateMesh(argv[1], "result.msh", updatedNodes);

    return 0;
}