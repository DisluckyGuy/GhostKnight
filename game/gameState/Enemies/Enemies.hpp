#pragma once

#include <vector>
#include <iostream>
#include "../../../cppGameEngine/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"
#include "Turret.hpp"
#include "Monster.hpp"

class Enemies {

    public:

    Enemies(weaponManager* weapons, Map* map, sf::Sprite* target);

    void setTarget(sf::Sprite* target);

    Turret* getTurret(int index);
    std::vector<Turret>* getTurrets();

    Monster* getMonster(int index);
    std::vector<Monster>* getMonsters();

    void update();
    void render();

    private:

    Map* map;

    sf::Clock waveCooldown;
    Turret turret;
    Monster monster;
    std::vector<Turret> turrets;
    std::vector<Monster> monsters;
    std::vector<sf::Sprite> enemySpawnTargets;
    sf::Sprite* target;
    sf::Sprite spawnTarget;
    weaponManager* weapons;
    sf::Texture enemyTexture;
    sf::Sprite turretHead;
    sf::Sprite turretBase;
    sf::Sprite turretBullet;
    sf::Sprite monsterSprite;
    int maxTurrets;
    int maxMonsters;

    void initSpawnTarget();
    void initTurret();
    void initMonster();
    void spawnTargets(int turretAmount, int monsterAmount);
    void spawnTurrets(Turret &turret, int amount);
    void spawnMonsters(Monster &monster, int amount);

};