cmake_minimum_required(VERSION 4.2.0)
project(ryt LANGUAGES CXX CUDA)
enable_language(CXX CUDA)

set(CMAKE_CUDA_ARCHITECTURES 89)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}) # Project Name is the executable

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/dependencies
)

file(GLOB_RECURSE source_files src/*.cpp src/*.cu)

# OpenMP 
find_package(OpenMP)

#CUDA ToolKit
find_package(CUDAToolkit REQUIRED)

# Link OpenMP and CUDA ToolKit
target_link_libraries(${PROJECT_NAME} PRIVATE 
    OpenMP::OpenMP_CXX CUDA::cudart)

target_sources(${PROJECT_NAME} PRIVATE ${source_files})

