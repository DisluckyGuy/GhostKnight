#pragma once

#include <vector>
#include <iostream>
#include "../../ge/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"


    

class Turret {

    private:

    struct Bullet {
        sf::Sprite sprite;
        sf::Vector2f velocity;
    };

    Map* map;
    ge::Data* data;
    unsigned int bulletVelocity;
    unsigned int fireRate;
    unsigned int distanceMin;
    float distX;
    float distY;

    void updateHead(sf::Sprite *target);
    void updateBullets();

    public:

    sf::Clock fireClock;

    sf::Sprite base;
    sf::Sprite head;
    sf::Sprite* target;
    Bullet bullet;
    std::vector<Bullet> bullets;
    
    Turret(ge::Data* data, Map* map, sf::Sprite* target);
    ~Turret();

    void init(sf::Sprite base, sf::Sprite head, sf::Sprite bullet);

    void shoot();

    void update();
    void render();

};