#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
#include <array>
#include <iostream>

using namespace std;
using namespace sf;

enum weaponState {
    Held,
    Dropped,
};

class Player
{
private:

    //private variables
    
    float velocity;
    Texture playerWeaponTexture;
    Sprite legLeft;
    Sprite legRight;
    Sprite player;
    pair<Sprite,weaponState> weapon;
    array<bool,4> direction;
    array<Texture,3> leftWalkAnimation;
    array<Texture,3> rightWalkAnimation;
    bool EHeld;
    Clock walkClock;
    Time walkTimer;
    int walkRate;
    bool leftDown;
    bool playerMoving;

    //private functions 

    void initVariables();
    void initPlayer();
    void initWeapons();

public:

    //constructor and destructor

    Player();
    ~Player();

    //accesssors

    Sprite* getPlayer();
    Sprite* getWeapon();
    int getWeaponState(int n = 0);
    float getVelocity();
    bool* getDirection(int n);

    //public functions

    void checkInputs();
    void updateLegs();
    void updatePlayer();
    void renderPlayer(RenderTarget* target);
    void updateWeapons();
    void renderWeapons(RenderTarget* target);

    //update & render

    void update();
    void render(RenderTarget* target);
};
