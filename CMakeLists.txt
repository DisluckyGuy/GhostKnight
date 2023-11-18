cmake_minimum_required(VERSION 3.5.0)
project(GhostKight VERSION 0.1.0)


find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
INCLUDE_DIRECTORIES(
    "ge/src/include"
)

LINK_DIRECTORIES(
    "ge/src/lib"
)
#target_include_directories(GhostKight PUBLIC ${DIRECTORY}/**)
add_executable(GhostKight main.cpp)
target_link_libraries(GhostKight PRIVATE sfml-system sfml-network sfml-graphics sfml-window)  