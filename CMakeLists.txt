cmake_minimum_required(VERSION 4.2.0)
project(ryt LANGUAGES CXX CUDA)
enable_language(CXX CUDA)

set(CMAKE_CUDA_ARCHITECTURES 89)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OpenMP 
find_package(OpenMP)

#CUDA ToolKit
find_package(CUDAToolkit REQUIRED)

file(GLOB_RECURSE RYT_SOURCES
src/*.cpp
src/*.cu
)

add_library(ryt SHARED ${RYT_SOURCES})

target_include_directories(ryt PUBLIC
include/
dependencies/
)

set_target_properties(ryt PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

# Link OpenMP and CUDA ToolKit
target_link_libraries(ryt PUBLIC
    OpenMP::OpenMP_CXX CUDA::cudart)

option(RYT_BUILD_EXAMPLES "Build Examples" ON)

if(RYT_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
