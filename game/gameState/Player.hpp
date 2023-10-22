#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <array>
#include <iostream>
#include "../ge/ge.hpp"
#include "map.hpp"

enum weaponState {
    Held,
    Dropped,
};

class Player
{
private:

    //private variables


    
    ge::Data* data;
    //Map map = Map(data);
    float velocity;
    sf::Texture playerWeaponTexture;
    sf::Sprite legLeft;
    sf::Sprite legRight;
    sf::Sprite player;
    int health;
    int shield;
    sf::Sprite healthBar;
    sf::Sprite shieldBar;
    sf::Vector2i healthPos;
    sf::Vector2i shieldPos;
    sf::Vector2i healthPosWin;
    sf::RectangleShape healthAmount;
    sf::RectangleShape shieldAmount;
    std::pair<sf::Sprite,weaponState> weapon;
    std::array<bool,4> direction;
    std::array<sf::Texture,3> leftWalkAnimation;
    std::array<sf::Texture,3> rightWalkAnimation;
    std::vector<sf::RectangleShape> healthRects;
    std::vector<sf::RectangleShape> shieldRects;
    bool EHeld;
    sf::Clock walkClock;
    sf::Time walkTimer;
    int walkRate;
    bool leftDown;
    bool playerMoving;

    //private functions 

    void initVariables();
    void initHealth();
    void initPlayer();
    void initWeapons();

public:

    //constructor and destructor

    Player(ge::Data* data);
    ~Player();

    //accesssors

    sf::Sprite* getPlayer();
    sf::Sprite* getWeapon();
    int getWeaponState(int n = 0);
    float getVelocity();
    bool* getDirection(int n);

    //public functions

    void updateDirection();
    void checkInputs();
    void updateLegs();
    void updatePlayer();
    void renderPlayer();
    void updateHealth();
    void renderHealth();
    void updateWeapons();
    void renderWeapons();

    //update & render

    void update();
    void render();
};
