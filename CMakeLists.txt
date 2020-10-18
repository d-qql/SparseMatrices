cmake_minimum_required(VERSION 3.17)
project(SparseMatrices)

set(CMAKE_CXX_STANDARD 14)

add_executable(SparseMatrices main.cpp DOK.cpp DOK.h Core.h Triplet.h Solver.cpp Solver.h)