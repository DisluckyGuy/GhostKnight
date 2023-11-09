#include "Player.hpp"

void Player::initVariables()
{
    playerAnimation.setSprite(&player);
    playerAnimation.addFrame(sf::IntRect(0,0,35,52), 100);
    playerAnimation.addFrame(sf::IntRect(35,0,35,52), 100);
    playerAnimation.addFrame(sf::IntRect(70,0,35,52), 200);
    playerAnimation.addFrame(sf::IntRect(35,0,35,52), 100);
    flippedAnimation.setSprite(&player);
    flippedAnimation.addFrame(sf::IntRect(0,0,-35,52), 100);
    flippedAnimation.addFrame(sf::IntRect(0,0,-35,52), 100);
    flippedAnimation.addFrame(sf::IntRect(35,0,-35,52), 100);
    flippedAnimation.addFrame(sf::IntRect(70,0,-35,52), 200);
    flippedAnimation.addFrame(sf::IntRect(35,0,-35,52), 100);
    flippedAnimation.addFrame(sf::IntRect(0,0,-35,52), 100);
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
    player.setTexture(data->texture.getResource("playerTexture")[0]);
    player.setPosition(30.f,30.f);
    playerMoving = false;
}

Player::Player(ge::Data* data, Map* map, weaponManager* weapons)
{
    this->data = data;
    this->map = map;
    this->weapons = weapons;
    initVariables();
    initPlayer();
    initHealth();
}

Player::~Player()
{
    delete this->data;
    delete this->map;
    delete this->weapons;
}

sf::Sprite *Player::getPlayer()
{
    return &player;
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

void Player::updateDirection()
{
}

void Player::updateWeaponAngle()
{
    weaponStruct* weaponSt = weapons->getWeapon(0);
    sf::Vector2f MPV = ge::getMousePosView(data);
    float angle = ge::tools::findAngle(player, MPV);
    if (weaponSt->held) {
        weaponSt->angle = angle;
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

void Player::updatePlayer()
{
    checkInputs();
    checkCollisions();
}

void Player::updateWeapons()
{
    weaponStruct* weapon = weapons->getWeapon(0);
    float distX = abs(weapon->weaponSprite.getPosition().x - player.getPosition().x);
    float distY = abs(weapon->weaponSprite.getPosition().y - player.getPosition().y);
    if (weapon->held) {
        updateWeaponAngle();
        weapons->getWeapon(0)->weaponSprite.setPosition(player.getPosition().x + 15.f, player.getPosition().y + 28.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        if (!EHeld) {
            EHeld = true;
            if (distX < 50.f && distY < 50.f) {
                weapon->held = !weapon->held;
            }
        }
    } else {
        EHeld = false;
    }
}

void Player::renderWeapons()
{
}

void Player::renderPlayer()
{
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
    playerAnimation.play();
    updatePlayer();
    updateWeapons();
}

void Player::render()
{
    renderPlayer();
}
