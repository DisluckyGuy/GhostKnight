#include "Player.hpp"

//ge::Data ge::data;

void Player::initVariables()
{
    playerAnimation.setSprite(&player);
    playerAnimation.addFrame(sf::IntRect(0,0,35,50), 100);
    playerAnimation.addFrame(sf::IntRect(35,0,35,50), 100);
    playerAnimation.addFrame(sf::IntRect(70,0,35,50), 200);
    playerAnimation.addFrame(sf::IntRect(35,0,35,50), 100);
    playerRect = sf::IntRect(0,0,35,50);
    maxHealth = 5;
    maxShield = 5;
    health = maxHealth;
    shield = maxShield;
    velocity = 2.f;
    EHeld = false;
    walkRate = 300;
    leftDown = false;
    playerWeaponTexture = ge::data.texture.getResource("mainTexture")[0];
}

void Player::initPlayer()
{
    player.setTexture(ge::data.texture.getResource("playerTexture")[0]);
    player.setTextureRect(sf::IntRect(0,0,35,50));
    player.setPosition(30.f,30.f);
    playerMoving = false;
}
void Player::initHealthBar()
{
    healthBar.setTexture(ge::data.texture.getResource("playerTexture")[0]);
    healthBar.setTextureRect(sf::IntRect(0,52,181,73));
    healthBar.setPosition(ge::data.win.mapCoordsToPixel(sf::Vector2f(10,10)).x, ge::data.win.mapCoordsToPixel(sf::Vector2f(10,10)).y);

    healthBarRect.setFillColor(sf::Color::Red);
    healthBarRect.setSize(sf::Vector2f(140 / health, 30));
    healthBarRect.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(41,55)));
    for (int i = 0; i < health; i++) {
        healthVec.push_back(healthBarRect);
        healthBarRect.move(138 / shield, 0.f);
    }

    shieldBarRect.setFillColor(sf::Color(100,100,100));
    shieldBarRect.setSize(sf::Vector2f(140 / shield, 30));
    shieldBarRect.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(41,91)));
    for (int i = 0; i < shield; i++) {
        shieldVec.push_back(shieldBarRect);
        shieldBarRect.move(138 / shield, 0.f);
    }
}

void Player::checkBulletCollisions()
{
    std::vector<weaponStruct>* weaponsVec = weapons->getWeapons();
    
    for (int i = 0; i < weaponsVec->size(); i++) {
        for (int j = 0; j < enemies.getTurrets()->size(); j++) {

            for (int k = 0; k < weapons->getWeapon(i)->bullets.size(); k++) {
                if (enemies.getTurret(j)->base.getGlobalBounds().intersects(weapons->getWeapon(i)->bullets[k].getGlobalBounds()) && 
                enemies.getTurret(j)->alive) {
                    weapons->getWeapon(i)->bullets.erase(weapons->getWeapon(i)->bullets.begin() + k);
                    weapons->getWeapon(i)->Velocities.erase(weapons->getWeapon(i)->Velocities.begin() + k);
                    enemies.getTurret(j)->changeHealth(-2);
                }
            }
        }
        for (int j = 0; j < enemies.getMonsters()->size(); j++) {

            for (int k = 0; k < weapons->getWeapon(i)->bullets.size(); k++) {
                if (enemies.getMonster(j)->sprite.getGlobalBounds().intersects(weapons->getWeapon(i)->bullets[k].getGlobalBounds()) && 
                enemies.getMonster(j)->alive) {
                    weapons->getWeapon(i)->bullets.erase(weapons->getWeapon(i)->bullets.begin() + k);
                    weapons->getWeapon(i)->Velocities.erase(weapons->getWeapon(i)->Velocities.begin() + k);
                    enemies.getMonster(j)->changeHealth(-2);
                }
            }
        }
    }

    for (Turret &turret : *enemies.getTurrets()) {
        for (Bullet &bullet : turret.bullets) {
            if (bullet.sprite.getGlobalBounds().intersects(player.getGlobalBounds())) {
                if (health > 0) {
                    if (shield > 0) {
                        shield -= 1;
                    } else {
                        health -= 1;
                    }
                    shieldRegen.restart();
                }
            }
        }
    }

    for (Monster monster : *enemies.getMonsters()) {
        if (player.getGlobalBounds().intersects(monster.sprite.getGlobalBounds())) {
            if (damageCooldown.getElapsedTime().asMilliseconds() >= 1000) {
                damageCooldown.restart();
                if (shield > 0) {
                    shield -= 3;
                } else {
                    health -= 3;
                }
            }
        }
    }
    updateHealthBarRects();
    
}

Player::Player(Map* map, weaponManager* weapons) : enemies(weapons, map, &player)
{
    this->map = map;
    this->weapons = weapons;
    initVariables();
    initHealthBar();
    initPlayer();
}

Player::~Player()
{
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
    checkBulletCollisions();
}

void Player::updateWeaponAngle()
{
    weaponStruct* weaponSt = weapons->getWeapon(0);
    sf::Vector2f MPV = ge::getMousePosView(&ge::data);
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
    sf::Vector2f MPV = ge::getMousePosView(&ge::data);
    float angle = ge::tools::findAngle(player, MPV);
    if (playerMoving) {
        
        if ((angle > -90 && angle < 0) || (angle < 90 && angle > 0)) {
            playerAnimation.play();
        } else {
            playerAnimation.play(true);
        }
    } else {
        playerAnimation.reset();
        player.setTextureRect(sf::IntRect(0,0,35,50));
        if ((angle > -90 && angle < 0) || (angle < 90 && angle > 0)) {
            player.setTextureRect(sf::IntRect(0,0,35,50));
        } else {
            player.setTextureRect(ge::tools::flipTextureX(playerRect));
        }
    }
}

void Player::updateHealthBarRects()
{
    if (shield == maxShield) {
        return;
    }
    if (shieldRegen.getElapsedTime().asMilliseconds() >= 3000) {
        shieldRegen.restart();
        shield += 1;
    }
    for (int i = 0; i < shieldVec.size(); i++) {
        if (i >= shield) {
            shieldVec[i].setFillColor(sf::Color::Black);
        } else {
            shieldVec[i].setFillColor(sf::Color(100,100,100));
        }
    }
    
    if (health == maxHealth) {
        return;
    }
    for (int i = 0; i < healthVec.size(); i++) { 
        if (i >= health) {
            healthVec[i].setFillColor(sf::Color::Black);
        } else {
            healthVec[i].setFillColor(sf::Color::Red);
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

void Player::updateHealthBar()
{
    healthBar.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(10,10)).x, ge::data.win.mapPixelToCoords(sf::Vector2i(10,10)).y);
    healthBarRect.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(41,14)));
    shieldBarRect.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(41,49)));
    float posX = 51;
    for (sf::RectangleShape& rect : healthVec) {
        rect.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(posX,13)));
        posX += 140 / maxHealth;
    }
    posX = 51;
    for (sf::RectangleShape& rect : shieldVec) {
        rect.setPosition(ge::data.win.mapPixelToCoords(sf::Vector2i(posX,49)));
        posX += 140 / maxShield;
    }
}

void Player::renderHealthBar()
{
    for (sf::RectangleShape& rect : healthVec) {
        ge::data.win.draw(rect);
    }
    for (sf::RectangleShape& rect : shieldVec) {
        ge::data.win.draw(rect);
    }
    ge::data.win.draw(healthBar);
}

void Player::renderPlayer()
{
    ge::data.win.draw(player);
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
    renderHealthBar();
}
