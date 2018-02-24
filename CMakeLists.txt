cmake_minimum_required(VERSION 3.9)
project(Lab4_140019E_140)

set(CMAKE_CXX_STANDARD 11)

add_executable(Lab4_140019E_140 main.cpp sequential.cpp sequencial.h MatrixOp.h util.cpp util.h matrixOp.cpp matrixOp.h parallel.cpp parallel.h)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(SOURCE_FILES main.cpp optimized_code.cpp optimized_code.h optimized_code_2.cpp optimized_code_2.h)
add_executable(openmp_test_clion ${SOURCE_FILES})

#download OpenMP via http://tdm-gcc.tdragon.net/