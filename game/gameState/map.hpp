#pragma once
#include "../ge/ge.hpp"
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

    private:

    ge::Data* data;
    
    sf::Texture cellTexture;
    sf::Sprite wallCell;
    sf::Sprite emptyCell;
    std::array<std::string,50> mapStr;
    std::array<std::array<Cell,50>,50> mapArr;

    void initCells();
    void initMap();

    public:

    sf::Vector2i mousePosWin;
    sf::Vector2f mousePosView;

    Map(ge::Data *data);
    ~Map();

    std::array<std::array<Cell,50>,50>* getMap();

    void updateMousePos();

    void update();
    void render();

    

};