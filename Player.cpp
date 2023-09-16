#include "Player.hpp"

void Player::initVariables()
{
    velocity = 2.f;
    if (!playerWeaponTexture.loadFromFile("C:/Mostafa/Code/C++/main/Files/testFiles/ParkourGame/gameTexture.png")) {
        cout << "couldn't load player and weapon texture" << endl;
    }
    EHeld = false;
}

void Player::initPlayer()
{
    player.setTexture(playerWeaponTexture);
    player.setTextureRect(IntRect(0,0,30,40));
    player.setPosition(30.f,30.f);
}

void Player::initWeapons()
{
    weapon.first.setTexture(playerWeaponTexture);
    weapon.first.setTextureRect(IntRect(0,70,40,15));
    weapon.first.setOrigin(5.f,9.f);
    weapon.first.setPosition(130.f,100.f);
    weapon.second = Dropped;
}

Player::Player()
{
    initVariables();
    initPlayer();
    initWeapons();
}

Player::~Player()
{
}

Sprite *Player::getPlayer()
{
    return &player;
}

Sprite *Player::getWeapon()
{
    return &weapon.first;
}

int Player::getWeaponState(int n)
{
    return weapon.second;
}

float Player::getVelocity()
{
    return velocity;
}

bool* Player::getDirection(int n)
{
    if (n == 0) {
        return &direction[0];
    } else if (n == 1) {
        return &direction[1];
    } else if (n == 2) {
        return &direction[2];
    } else if (n == 3) {
        return &direction[3];
    } else {
        return &direction[0];
    }
}

void Player::checkInputs()
{
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        player.move(0.f,-velocity);
        direction[0] = true;
    } else if (Keyboard::isKeyPressed(Keyboard::S)) {
        player.move(0.f,velocity);
        direction[1] = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        player.move(-velocity,0.f);
        direction[2] = true;
    } else if (Keyboard::isKeyPressed(Keyboard::D)) {
        player.move(velocity,0.f);
        direction[3] = true;        
    }
    if (!Keyboard::isKeyPressed(Keyboard::W)) {
        direction[0] = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::S)) {
        direction[1] = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::A)) {
        direction[2] = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::D)) {
        direction[3] = false;        
    }
}

void Player::updatePlayer()
{
    checkInputs();
}

void Player::updateWeapons()
{
    float distX = abs(weapon.first.getPosition().x - player.getPosition().x);
    float distY = abs(weapon.first.getPosition().y - player.getPosition().y);
    if (weapon.second == Held) {
        weapon.first.setPosition(player.getPosition().x + 15.f, player.getPosition().y + 28.f);
    }
    if (Keyboard::isKeyPressed(Keyboard::E) && weapon.second == Dropped) {
        if (!EHeld) {
            EHeld = true;
            if (distX < 30.f && distY < 30.f && weapon.second == Dropped) {
                weapon.second = Held;
            }
        }
    } else {
        EHeld = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::T) && weapon.second == Held) {
        weapon.first.setRotation(0);
        weapon.second = Dropped;
    }
}

void Player::renderWeapons(RenderTarget* target)
{
    target->draw(weapon.first);
}

void Player::renderPlayer(RenderTarget* target)
{
    target->draw(player);
}

void Player::update()
{
    updatePlayer(); 
    updateWeapons();
}

void Player::render(RenderTarget* target)
{
    if (weapon.second == Dropped) 
        renderWeapons(target);
    renderPlayer(target);
    if (weapon.second == Held) 
        renderWeapons(target);
}
