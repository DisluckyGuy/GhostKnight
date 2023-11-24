#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "weaponManager.hpp"
#include "Enemies/Enemies.hpp"
#include "../../cppGameEngine/ge.hpp"
#include "map.hpp"

enum weaponState {
    Held,
    Dropped,
};

class Player
{
    
public:

    Player(Map* map, weaponManager* weapons);
    ~Player();

    sf::Sprite* getPlayer();
    float getVelocity();

    void updatePlayer();
    void renderPlayer();
    void updateWeapons();
    void renderWeapons();
    void updateHealthBar();
    void renderHealthBar();

    void update();
    void render();

private:
    sf::Clock damageCooldown;
    Map* map;
    weaponManager* weapons;
    Enemies enemies;
    float velocity;
    sf::Texture playerWeaponTexture;
    Animation playerAnimation;
    Animation flippedAnimation;
    sf::IntRect playerRect;
    sf::Sprite player;
    sf::Sprite healthBar;
    sf::RectangleShape healthBarRect;
    sf::RectangleShape shieldBarRect;
    sf::Clock shieldRegen;
    int maxHealth;
    int maxShield;
    int health;
    int shield;
    std::vector<sf::RectangleShape> healthVec;
    std::vector<sf::RectangleShape> shieldVec;
    bool EHeld;
    int walkRate;
    bool leftDown;
    bool playerMoving;
    

    //private functions 

    void initVariables();
    void initPlayer();
    void initHealthBar();

    void checkBulletCollisions();

    void checkCollisions();
    void updateWeaponAngle();
    void checkInputs();
    void updateHealthBarRects();

};
