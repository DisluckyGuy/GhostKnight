#pragma once

#include <vector>
#include <iostream>
#include "../../../cppGameEngine/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"

enum class MonsterMode {
    Follow,
    Attack,
    Wander,
};

class Monster {
    
    public:

    Map* map;
    sf::Vector2f distance;
    sf::Vector2f velocity;
    sf::Sprite sprite;

    int health;
    float speed;
    bool alive;
    MonsterMode mode;

    Monster(Map* map, sf::Sprite* target);
    void setSprite(sf::Sprite sprite);

    void changeHealth(int amount);

    void updateAngle();
    void updateMode();
    void updateWander();
    void updateFollow();
    void updateAttack();
    
    void update();
    void render();

    private: 

    float angle;
    
    sf::Texture tempTexture;
    Animation animation;
    sf::IntRect mainRect;
    sf::IntRect flippedRect;

    int wanderspeed;
    int flowSpeed;
    int attackSpeed;

    bool isAttacking;
    

    sf::Clock wanderClock;
    sf::Clock attackClock;

    sf::Vector2f minFollowDistance;
    sf::Vector2f minAttackDistance;

    sf::Sprite* target;
    

    void checkCollisions();
    void attack(float angle, sf::Vector2f velocity);

};