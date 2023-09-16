#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include "Player.hpp"

using namespace std;
using namespace sf;

enum cellType {
    Wall,
    Empty
};
class Game
{
private:
    
    //private variables
    typedef array<pair<Sprite,cellType>,50> mapRow;
    typedef pair<Sprite,cellType> mapPair;
    
    float pi;
    VideoMode VM;
    RenderWindow* win;
    View mainView;
    Event event;
    Player player;
    Vector2i mousePosWin;
    Vector2f mousePosView;
    Texture cellTexture;
    Sprite wallCell;
    Sprite emptyCell;
    CircleShape bullet;
    vector<pair<CircleShape,Vector2f>> bullets;
    array<string,50> mapStr;
    array<array<pair<Sprite,cellType>,50>,50> map;
    double angle;
    double angleR;
    double slope;
    int fireRate;
    float bulletSpeed;
    Clock fireRateClock;
    Time fireRateTimer;

    //private functions
    
    void initVariables();
    void initViews();
    void initWindow();
    void initMap();
    void initBullets();

public:

    //Constructor and destructor

    Game();
    ~Game();

    

    //accessors

    const bool isOpen();

    //public functions

    void pollEvents();

    //Update & Render

    void updateViews();
    void updateMousePos();
    void checkCollisions();
    void setAngleAndSlope();
    void updateWeaponsGame();
    void renderMap();
    void updateBullets();
    void renderBullets();
    void update();
    void render();
    
};

