#include <vector>
#include <array>
#include <iostream>
#include <memory>
#include "../ge/ge.hpp"
#include "Player.hpp"
#include "weaponManager.hpp"
#include "map.hpp"

class Game : public ge::State
{
private:
    
    //private variables
    typedef std::array<std::pair<sf::Sprite,cellType>,50> mapRow;
    typedef std::pair<sf::Sprite,cellType> mapPair;
    //View mainView;
    sf::Event event;
    Map* map = new Map(data);
    Player player = Player(data, map);
    

    sf::CircleShape bullet;
    int fireRate;
    float bulletSpeed;
    bool idleAnimation;
    weaponManager gun = weaponManager(data);
    //private functions
    void initVariables();
    void initViews();
    void initBullets();

public:

    //Constructor and destructor

    Game(ge::Data *data);
    ~Game();

    //Update & Render

    void updateViews();
    void updateHealthGame();
    void checkCollisions();
    void updateWeaponsGame();
    void renderMap();
    void updateBullets();
    void renderBullets();
    void update();
    void render();
    
};

