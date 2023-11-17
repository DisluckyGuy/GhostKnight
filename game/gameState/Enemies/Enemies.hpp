#pragma once

#include <vector>
#include <iostream>
#include "../../ge/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"
#include "Turret.hpp"
#include "Monster.hpp"

class Enemies {

    private:

    Map* map;
    ge::Data* data;
    Turret turret;
    std::vector<Turret> turrets;
    sf::Sprite* target;
    weaponManager* weapons;
    sf::Texture enemyTexture;
    sf::Sprite turretHead;
    sf::Sprite turretBase;
    sf::Sprite turretBullet;

    void initTurret();

    public:

    Enemies(ge::Data* data, weaponManager* weapons, Map* map, sf::Sprite* target);

    void setTarget(sf::Sprite* target);

    void getTurret(int index);
    void getTurrets();

    void update();
    void render();

};