cmake_minimum_required(VERSION 3.5.0)
project(GhostKight)

add_executable(GhostKight main.cpp
    game/gameState/Game.cpp
    game/gameState/Player.cpp
    game/gameState/weaponManager.cpp
    game/gameState/Map.cpp
    game/gameState/Enemies/Enemies.cpp
    game/gameState/Enemies/Turret.cpp
    game/gameState/Enemies/Monster.cpp
    )

target_link_libraries(GhostKight PUBLIC sfml-system sfml-network sfml-graphics sfml-window)  