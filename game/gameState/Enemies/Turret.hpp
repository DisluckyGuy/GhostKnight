#pragma once

#include <vector>
#include <iostream>
#include "../../../cppGameEngine/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"


struct Bullet {
    sf::Sprite sprite;
    sf::Vector2f velocity;
};    

class Turret {

    public:

    sf::Clock fireClock;

    sf::Sprite base;
    sf::Sprite head;
    sf::Sprite* target;
    int health;
    Bullet bullet;
    std::vector<Bullet> bullets;
    
    Turret(Map* map, sf::Sprite* target);
    ~Turret();

    void init(sf::Sprite base, sf::Sprite head, sf::Sprite bullet);

    void changeHealth(int change);
    void shoot();

    void updateBullets();

    void update();
    void render();

    private:

    Map* map;
    
    unsigned int bulletVelocity;
    unsigned int fireRate;
    unsigned int distanceMin;
    float distX;
    float distY;

    

    void updateHead(sf::Sprite *target);
    

};