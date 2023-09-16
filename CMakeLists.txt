cmake_minimum_required(VERSION 3.5.0)
project(parkour VERSION 0.1.0 LANGUAGES C CXX)

add_executable(parkour Player.hpp Player.cpp Game.hpp Game.cpp main.cpp)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(parkour PRIVATE sfml-system sfml-network sfml-graphics sfml-window)