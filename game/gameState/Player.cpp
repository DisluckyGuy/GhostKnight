#include "Player.hpp"

void Player::initVariables()
{
    playerAnimation.setSprite(&player);
    playerAnimation.addFrame(sf::IntRect(0,0,35,52), 100);
    playerAnimation.addFrame(sf::IntRect(35,0,35,52), 100);
    playerAnimation.addFrame(sf::IntRect(70,0,35,52), 200);
    playerAnimation.addFrame(sf::IntRect(35,0,35,52), 100);
    playerRect = sf::IntRect(0,0,35,52);
    health = 7;
    shield = 5;
    velocity = 2.f;
    EHeld = false;
    walkRate = 300;
    leftDown = false;
    playerWeaponTexture = data->texture.getResource("mainTexture")[0];
}

void Player::initPlayer()
{
    player.setTexture(data->texture.getResource("playerTexture")[0]);
    player.setPosition(30.f,30.f);
    playerMoving = false;
}

Player::Player(ge::Data* data, Map* map, weaponManager* weapons) : enemies(data, weapons, map, &player)
{
    this->data = data;
    this->map = map;
    this->weapons = weapons;
    initVariables();
    initPlayer();
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

void Player::checkCollisions()
{
    for (mapRow &i : *map->getMap()) {
        for (Cell &j : i) {
            if (j.type == cellType::Wall) {
                ge::tools::isColliding(player, j.sprite, velocity);
            }
        }
    }
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
        playerMoving = true;
        player.move(0.f,-velocity);
        
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        playerMoving = true;
        player.move(0.f,velocity);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        playerMoving = true;
        player.move(-velocity,0.f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerMoving = true;
        player.move(velocity,0.f);
    }
    if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
        playerMoving = false;
    }
    sf::Vector2f MPV = ge::getMousePosView(data);
    float angle = ge::tools::findAngle(player, MPV);
    if (playerMoving) {
        
        if ((angle > -90 && angle < 0) || (angle < 90 && angle > 0)) {
            playerAnimation.play();
        } else {
            playerAnimation.play(true);
        }
    } else {
        playerAnimation.reset();
        player.setTextureRect(sf::IntRect(0,0,35,52));
        if ((angle > -90 && angle < 0) || (angle < 90 && angle > 0)) {
            player.setTextureRect(sf::IntRect(0,0,35,52));
        } else {
            player.setTextureRect(ge::tools::flipTextureX(playerRect));
        }
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
        weapons->getWeapon(0)->weaponSprite.setPosition(player.getPosition().x + 18.f, player.getPosition().y + 37.f);
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

void Player::update()
{
    updatePlayer();
    updateWeapons();
    enemies.update();
}

void Player::render()
{
    enemies.render();
    renderPlayer();
}
