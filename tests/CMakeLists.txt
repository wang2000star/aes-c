# Add include directories for tests
include_directories(${CMAKE_SOURCE_DIR})
include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(test test.cpp)
target_link_libraries(test PUBLIC  Symmetric)