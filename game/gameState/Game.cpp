#include "Game.hpp"

void Game::initVariables()
{
    idleAnimation = false;
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
    delete this->map;
    delete this->weapons;
    delete this->player;
}


void Game::updateViews()
{
}


void Game::updateHealthGame()
{
    
}

void Game::checkCollisions()
{

}

void Game::updateWeapons()
{
    
}

void Game::renderMap()
{
    for (std::array<Cell,50> &i : *map->getMap()) {
        for (Cell &j : i) {
            data->win.draw(j.sprite);
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
    map->update();
    map->updateMousePos();
    player->update();
    weapons->update();
    updateViews();
}

void Game::render()
{
    map->render();
    if (!weapons->getWeapon(0)->held) 
        data->win.draw(weapons->getWeapons()->begin()->weaponSprite);
    player->render();
    if (weapons->getWeapon(0)->held) 
        data->win.draw(weapons->getWeapon(0)->weaponSprite);
    weapons->render();
}
