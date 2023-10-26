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

}

void Game::updateWeaponsGame()
{
    
}

void Game::renderMap()
{
    for (mapRow &i : *map->getMap()) {
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
    map->update();
    map->updateMousePos();
    player.update();
    updateViews();
    updateWeaponsGame();
}

void Game::render()
{
    map->render();
    player.render();
}
