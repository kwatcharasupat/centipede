# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(Chap1 VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/code/Timber.cpp)

# Add the executable
add_executable(Chap1 ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/../SFML/include)

link_directories(${PROJECT_SOURCE_DIR}/../SFML/lib)

# Link the executable to the libraries in the lib directory
target_link_libraries(Chap1 PUBLIC sfml-graphics sfml-system sfml-window)

