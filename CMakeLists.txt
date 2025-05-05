cmake_minimum_required(VERSION 3.16)

project(AES LANGUAGES CXX)

## Use -std=c11 as default.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## if Debug 
#set(CMAKE_BUILD_TYPE "Debug")

## if Release
set(CMAKE_BUILD_TYPE "Release" )

# 添加编译选项
add_compile_options(-O2 -march=native)
#add_compile_options(-O3 -march=native)
#add_compile_options(-mavx2)
#add_compile_options(-pthread -fopenmp)

#包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# add symmetric library
aux_source_directory("${CMAKE_SOURCE_DIR}/src" SYMMETRIC_SRC_LIST)
add_library(Symmetric ${SYMMETRIC_SRC_LIST})

# # 查找 OpenMP 并链接
# find_package(OpenMP REQUIRED)
# if(OpenMP_CXX_FOUND)
#     target_link_libraries(Symmetric PUBLIC OpenMP::OpenMP_CXX)
# endif()

# Output SYMMETRIC_SRC_LIST for debugging
message(STATUS "SYMMETRIC_SRC_LIST: ${SYMMETRIC_SRC_LIST}")

add_subdirectory(tests)