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
    playerMoving = false;
}

void Player::initWeapons()
{
    //weapon.first.setTexture(playerWeaponTexture);
    //weapon.first.setTextureRect(sf::IntRect(0,70,40,15));
    //weapon.first.setOrigin(5.f,7.f);
    //weapon.first.setPosition(130.f,100.f);
    //weapon.second = Dropped;
}

Player::Player(ge::Data* data, Map* map) : weapons(data)
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
    weaponStruct* weaponSt = weapons.getWeapon(0);
    sf::Sprite* weapon = &weaponSt->weaponSprite;
    sf::Vector2f MPV = ge::getMousePosView(data);
    float angle = ge::tools::findAngle(player, MPV);
    if (weaponSt->held) {
        weapon->setRotation(angle);
        if (angle <= 90.f && angle >= -90.f) {
            weapon->setTextureRect(sf::IntRect(0,70,40,15));
        } else {
            weapon->setTextureRect(sf::IntRect(40,70,40,15));
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

void Player::updatePlayer()
{
    checkInputs();
    checkCollisions();
}

void Player::updateWeapons()
{
    weaponStruct* weapon = weapons.getWeapon(0);
    float distX = abs(weapon->weaponSprite.getPosition().x - player.getPosition().x);
    float distY = abs(weapon->weaponSprite.getPosition().y - player.getPosition().y);
    if (weapon->held) {
        updateWeaponAngle();
        weapons.getWeapon(0)->weaponSprite.setPosition(player.getPosition().x + 15.f, player.getPosition().y + 28.f);
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
    for (mapRow &mp : *map->getMap()) {
        for (mapPair &mpair : mp) {
            for (weaponStruct &weapon : *weapons.getWeapons()) {
                for (int i = 0; i < weapon.bullets.size(); i++) {
                    if (mpair.first.getGlobalBounds().intersects(weapon.bullets[i].getGlobalBounds()) && mpair.second == cellType::Wall) {
                        weapon.bullets.erase(weapon.bullets.begin() + i);
                        weapon.Velocities.erase(weapon.Velocities.begin() + i);
                    }
                }
            }
        }
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
    updatePlayer();
    updateWeapons();
    weapons.update();
}

void Player::render()
{
    if (!weapons.getWeapon(0)->held) 
        data->win.draw(weapons.getWeapons()->begin()->weaponSprite);
        
    renderPlayer();
    if (weapons.getWeapon(0)->held) 
        data->win.draw(weapons.getWeapons()->begin()->weaponSprite);
    for ( sf::Sprite &i : weapons.getWeapon(0)->bullets) {
        data->win.draw(i);
    }
}
