#include "Player.hpp"

void Player::initVariables()
{
    health = 7;
    shield = 5;
    velocity = 2.f;
    EHeld = false;
    walkRate = 300;
    leftDown = false;
    playerWeaponTexture = data->texture.getResource("mainTexture")[0];
}

void Player::initHealth()
{
    healthBar.setTexture(playerWeaponTexture);
    healthBar.setTextureRect(sf::IntRect(0,87,97,21));
    healthPos.x = 10;
    healthPos.y = 52;
    healthBar.setPosition(0,42);
    //healthBar.setScale(2.f,2.f);
    shieldBar.setTexture(playerWeaponTexture);
    shieldBar.setTextureRect(sf::IntRect(0,108,97,21));
    shieldPos.x = 10;
    shieldPos.y = 10;
    shieldBar.setPosition(0,0);
    //shieldBar.setScale(2.f,2.f);
    healthAmount.setSize(sf::Vector2f(10.f,11.f));
    healthAmount.setPosition(0.f,0.f);
    healthAmount.setFillColor(sf::Color::Red);
    shieldAmount.setSize(sf::Vector2f(14.f,11.f));
    shieldAmount.setPosition(0.f,0.f);
    shieldAmount.setFillColor(sf::Color::White);
    int posxOffset = 24;
    int posyOffset = 5;
    for (int i = 0; i < 7; i++) {
        healthAmount.setPosition(healthBar.getPosition().x + posxOffset, healthBar.getPosition().y + posyOffset);
        healthRects.push_back(healthAmount);
        posxOffset += 10;
    }
    posxOffset = 24;
    for (int i = 0; i < 5; i++) {
        shieldAmount.setPosition(shieldBar.getPosition().x + posxOffset, shieldBar.getPosition().y + posyOffset);
        shieldRects.push_back(shieldAmount);
        posxOffset += 14;
    }
}

void Player::initPlayer()
{
    player.setTexture(data->texture.getResource("player")[0]);
    player.setPosition(30.f,30.f);
    //legLeft.setTexture(playerWeaponTexture);
    //legLeft.setTextureRect(IntRect(80,70,4,7));
    //legLeft.setOrigin(1,2);
    //legLeft.setPosition(player.getPosition().x + 8, player.getPosition().y + 36);
    //legRight.setTexture(playerWeaponTexture);
    //legRight.setTextureRect(IntRect(84,70,4,7));
    //legRight.setOrigin(1,2);
    //legRight.setPosition(player.getPosition().x + 18 , player.getPosition().y + 36);
    playerMoving = false;
}

void Player::initWeapons()
{
    weapon.first.setTexture(playerWeaponTexture);
    weapon.first.setTextureRect(sf::IntRect(0,70,40,15));
    weapon.first.setOrigin(5.f,7.f);
    weapon.first.setPosition(130.f,100.f);
    weapon.second = Dropped;
}

Player::Player(ge::Data* data, Map* map)
{
    this->data = data;
    this->map = map;
    initVariables();
    initPlayer();
    initHealth();
    initWeapons();
}

Player::~Player()
{
    delete this->data;
    delete this->map;
}

sf::Sprite *Player::getPlayer()
{
    return &player;
}

sf::Sprite *Player::getWeapon()
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

void Player::checkCollisions()
{
    for (mapRow &i : *map->getMap()) {
        for (mapPair &j : i) {
            if (j.second == cellType::Wall) {
                ge::tools::isColliding(player, j.first, velocity);
            }
        }
    }
}

void Player::checkInputs()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player.move(0.f,-velocity);
        direction[0] = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player.move(0.f,velocity);
        direction[1] = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player.move(-velocity,0.f);
        direction[2] = true;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player.move(velocity,0.f);
        direction[3] = true;        
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction[0] = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction[1] = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        direction[2] = false;
    }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        direction[3] = false;        
    }
}

void Player::updateLegs()
{
    
    walkTimer = walkClock.getElapsedTime();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
    || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerMoving = true;
        if (walkTimer.asMilliseconds() >= walkRate) {
            if (leftDown) {
                leftDown = false;
            } else {
                leftDown = true;
            }
            walkClock.restart();
        }
    } else {
        playerMoving = false;
    }
    //if (leftDown && playerMoving) {
    //    legLeft.setPosition(player.getPosition().x + 9, player.getPosition().y + 34);
    //    legRight.setPosition(player.getPosition().x + 18, player.getPosition().y + 36);
    //} else if (!leftDown && playerMoving) {
    //    legLeft.setPosition(player.getPosition().x + 9, player.getPosition().y + 36);
    //    legRight.setPosition(player.getPosition().x + 18, player.getPosition().y + 34);
    //} else {
    //    legLeft.setPosition(player.getPosition().x + 9, player.getPosition().y + 36);
    //    legRight.setPosition(player.getPosition().x + 18, player.getPosition().y + 36);
    //}
}

void Player::updatePlayer()
{
    checkInputs();
    checkCollisions();
    updateLegs();
}

void Player::updateWeapons()
{
    float distX = abs(weapon.first.getPosition().x - player.getPosition().x);
    float distY = abs(weapon.first.getPosition().y - player.getPosition().y);
    if (weapon.second == Held) {
        weapon.first.setPosition(player.getPosition().x + 15.f, player.getPosition().y + 28.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && weapon.second == Dropped) {
        if (!EHeld) {
            EHeld = true;
            if (distX < 30.f && distY < 30.f && weapon.second == Dropped) {
                weapon.second = Held;
            }
        }
    } else {
        EHeld = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) && weapon.second == Held) {
        weapon.first.setRotation(0);
        weapon.second = Dropped;
    }
}

void Player::renderWeapons()
{
    data->win.draw(weapon.first);
}

void Player::renderPlayer()
{
    //data->win.draw(legLeft);
    //data->win.draw(legRight);
    data->win.draw(player);
}

void Player::updateHealth()
{
    int posxOffset = 24;
    int posyOffset = 5;
    for (sf::RectangleShape &i : healthRects) {
        i.setPosition(healthBar.getPosition().x + posxOffset, healthBar.getPosition().y + posyOffset);
        posxOffset += 10;
    }
    posxOffset = 24;
    for (sf::RectangleShape &i : shieldRects) {
        i.setPosition(shieldBar.getPosition().x + posxOffset, shieldBar.getPosition().y + posyOffset);
        posxOffset += 14;
    }
}

void Player::renderHealth()
{
    sf::Vector2f healthPosWin = data->win.mapPixelToCoords(healthPos);
    healthBar.setPosition(healthPosWin);
    sf::Vector2f shieldPosWin = data->win.mapPixelToCoords(shieldPos);
    shieldBar.setPosition(shieldPosWin);
    data->win.draw(healthBar);
    data->win.draw(shieldBar);
    for (sf::RectangleShape &i : healthRects) {
        data->win.draw(i);
    }
    for (sf::RectangleShape &i : shieldRects) {
        data->win.draw(i);
    }
}

void Player::update()
{
    updateHealth(); 
    updatePlayer();
    updateWeapons();
}

void Player::render()
{
    if (weapon.second == Dropped) 
        renderWeapons();
    renderPlayer();
    if (weapon.second == Held) 
        renderWeapons();
    //renderHealth();
}
