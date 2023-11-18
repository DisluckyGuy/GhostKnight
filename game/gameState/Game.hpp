#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include "../../cppGameEngine/ge.hpp"
#include "Player.hpp"
#include "weaponManager.hpp"
#include "map.hpp"

class Game : public ge::State
{


public:

    //Constructor and destructor

    Game(ge::Data *data);
    ~Game();

    //Update & Render

    void updateViews();
    void updateHealthGame();
    void checkCollisions();
    void updateWeapons();
    void renderMap();
    void updateBullets();
    void renderBullets();
    void update();
    void render();

private:
    
    //private variables
    typedef std::array<std::pair<sf::Sprite,cellType>,50> mapRow;
    typedef std::pair<sf::Sprite,cellType> mapPair;
    //View mainView;
    sf::Event event;
    Map* map = new Map();
    weaponManager* weapons = new weaponManager(map);
    Player* player = new Player(/*data,*/ map, weapons);
    

    sf::CircleShape bullet;
    int fireRate;
    float bulletSpeed;
    bool idleAnimation;
    //private functions
    void initVariables();
    void initViews();
    void initBullets();
};

