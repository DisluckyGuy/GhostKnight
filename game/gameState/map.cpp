#include "map.hpp"

void Map::initCells()
{
    wallCell.setTexture(cellTexture);
    wallCell.setTextureRect(sf::IntRect(0,40,30,30));
    emptyCell.setTexture(cellTexture);
    emptyCell.setTextureRect(sf::IntRect(30,40,30,30));

}

void Map::initMap()
{
    for (int i = 0; i < mapStr.size(); i++) {
        if (i == 0 || i == 49) {
            mapStr[i] = "##################################################";
        } else {
            mapStr[i] = "#                                                #";
        }
    }
    for (int i = 0; i < mapArr.size(); i++) {
        for (int j = 0; j < mapArr.size(); j++) {
            if (mapStr[i][j] == '#') {
                mapArr[i][j].sprite = wallCell;
                mapArr[i][j].sprite.setPosition(static_cast<float>(i * 30), static_cast<float>(j * 30));
                mapArr[i][j].type = cellType::Wall;
                
            } else if (mapStr[i][j] == ' ') {
                mapArr[i][j].sprite = emptyCell;
                mapArr[i][j].type = cellType::Empty;
                mapArr[i][j].sprite.setPosition(static_cast<float>(i * 30), static_cast<float>(j * 30));
            }
        }
    }
    cellTexture = data->texture.getResource("mainTexture")[0];
}

Map::Map(ge::Data *data)
{
    this->data = data;
    initCells();
    initMap();
}

Map::~Map() 
{
}

std::array<std::array<Cell,50>,50>* Map::getMap()
{
    return &mapArr;
}

void Map::updateMousePos()
{
    mousePosWin = sf::Mouse::getPosition();
    mousePosView = data->win.mapPixelToCoords(mousePosWin);
}

void Map::update()
{
}

void Map::render()
{
    for (mapRow &i : mapArr) {
        for (Cell &j : i) {
            data->win.draw(j.sprite);
        }
    }
}
