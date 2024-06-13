cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME FEM_project)

project(
        ${PROJECT_NAME}
        VERSION 2.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen
        GIT_TAG 3.4.0)
set(EIGEN_BUILD_DOC OFF)
FetchContent_MakeAvailable(eigen)
set(EIGEN_BUILD_DOC OFF)

#include(FetchContent)
#FetchContent_Declare(gmsh
#        GIT_REPOSITORY https://gitlab.onelab.info/gmsh/gmsh
#        GIT_TAG gmsh_4_13_1)
#set(ENABLE_BUILD_SHARED  ON)
#FetchContent_MakeAvailable(gmsh)
#target_link_options(shared PUBLIC "-lgmp")
#target_link_options(shared PUBLIC "-lwsock32")
#target_link_options(shared PUBLIC "-lWs2_32")
#target_link_options(shared PUBLIC "-lAdvApi32")
#target_link_libraries(shared Ws2_32)
#target_link_libraries(shared wsock32)
#target_link_libraries(shared AdvApi32)
#
##include_directories(${gmsh_SOURCE_DIR}/api)

add_subdirectory(src)

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC
        Eigen3::Eigen
)
#target_link_libraries(
#        ${PROJECT_NAME}
#        PUBLIC
#        shared
#)
