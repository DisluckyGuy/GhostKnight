#pragma once
#include "../../cppGameEngine/ge.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>

enum class cellType {
    Wall,
    Empty
};

struct Cell {
    cellType type;
    sf::Sprite sprite;

};

typedef std::array<Cell,50> mapRow;

class Map {

    public:

    sf::Vector2i mousePosWin;
    sf::Vector2f mousePosView;

    Map();
    ~Map();

    std::array<std::array<Cell,50>,50>* getMap();

    void update();
    void render();

private:
    
    sf::Texture cellTexture;
    sf::Sprite wallCell;
    sf::Sprite emptyCell;
    std::array<std::string,50> mapStr;
    std::array<std::array<Cell,50>,50> mapArr;

    void initCells();
    void initMap();


};