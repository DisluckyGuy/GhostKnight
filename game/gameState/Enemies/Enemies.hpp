#pragma once

#include <vector>
#include <iostream>
#include "../../../cppGameEngine/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"
#include "Turret.hpp"

class Enemies {

    public:

    Enemies(weaponManager* weapons, Map* map, sf::Sprite* target);

    void setTarget(sf::Sprite* target);

    void getTurret(int index);
    void getTurrets();

    void update();
    void render();

    private:

    Map* map;
    Turret turret;
    std::vector<Turret> turrets;
    sf::Sprite* target;
    weaponManager* weapons;
    sf::Texture enemyTexture;
    sf::Sprite turretHead;
    sf::Sprite turretBase;
    sf::Sprite turretBullet;
    int maxTurrets;

    void initTurret();
    void spawnTurrets(Turret &turret, int amount);

};