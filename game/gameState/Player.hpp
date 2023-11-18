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

    void checkCollisions();
    void updateWeaponAngle();
    void checkInputs();
    void updatePlayer();
    void renderPlayer();
    void updateWeapons();
    void renderWeapons();

    void update();
    void render();

private:

    Map* map;
    weaponManager* weapons;
    Enemies enemies;
    float velocity;
    sf::Texture playerWeaponTexture;
    Animation playerAnimation;
    Animation flippedAnimation;
    sf::IntRect playerRect;
    sf::Sprite player;
    int health;
    int shield;
    bool EHeld;
    sf::Clock walkClock;
    sf::Time walkTimer;
    int walkRate;
    bool leftDown;
    bool playerMoving;
    

    //private functions 

    void initVariables();
    void initPlayer();
};
