#include "Game.hpp"

void Game::initVariables()
{
    idleAnimation = false;
    gun.setFirerate(200);
}

void Game::initViews()
{

}

void Game::initBullets()
{
    fireRate = 100;
    bulletSpeed = 8;
    bullet.setFillColor(sf::Color::Yellow);
    bullet.setRadius(3);
}

Game::Game(ge::Data *data): ge::State(data)
{
    initViews();
    initVariables();
    initBullets();
}

Game::~Game()
{
    delete this->data;
}


void Game::updateViews()
{
}


void Game::updateHealthGame()
{
    
}

void Game::checkCollisions()
{
    float velocity = player.getVelocity();
    sf::Sprite* playerPtr = player.getPlayer(); 
    for (mapRow &i : *map.getMap()) {
        for (mapPair &j : i) {
            if (j.second == cellType::Wall) {
                ge::tools::isColliding(*playerPtr, j.first, velocity);
            }
        }
    }
}

void Game::updateWeaponsGame()
{
    sf::Sprite* weapon = player.getWeapon();
    float angle = ge::tools::findAngle(*player.getPlayer(),map.mousePosView);
    if (player.getWeaponState() == Held) {
        player.getWeapon()->setRotation(angle);
        if (angle <= 90.f && angle >= -90.f) {
            player.getWeapon()->setTextureRect(sf::IntRect(0,70,40,15));
        } else {
            player.getWeapon()->setTextureRect(sf::IntRect(40,70,40,15));
        }
    }
}

void Game::renderMap()
{
    for (mapRow &i : *map.getMap()) {
        for (mapPair &j : i) {
            data->win.draw(j.first);
        }
    }
}

void Game::updateBullets()
{

}

void Game::renderBullets()
{
    
}

void Game::update()
{
    map.update();
    map.updateMousePos();
    checkCollisions();
    player.update();
    updateViews();
    updateWeaponsGame();
}

void Game::render()
{
    map.render();
    player.render();
}
