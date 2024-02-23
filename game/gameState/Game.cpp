#include "Game.hpp"

//ge::Data ge::data;

void Game::initVariables()
{
}

void Game::initViews()
{
    sf::Sprite* playerSprite = player->getPlayer();
    playerView.setSize(sf::Vector2f(1280, 720));
    playerView.setCenter(playerSprite->getPosition().x + playerSprite->getGlobalBounds().width / 2, 
    playerSprite->getPosition().y + playerSprite->getGlobalBounds().height / 2);
    ge::data.win.setView(playerView);
}

Game::Game(ge::Data *data): ge::State(data)
{
    initViews();
    initVariables();
}

Game::~Game()
{
    delete this->map;
    delete this->weapons;
    delete this->player;
}


void Game::updateViews()
{
    sf::Sprite* playerSprite = player->getPlayer();
    playerView.setCenter((playerSprite->getPosition().x + playerSprite->getGlobalBounds().width / 2), 
    (playerSprite->getPosition().y + playerSprite->getGlobalBounds().height / 2));
    ge::data.win.setView(playerView);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) {
        if (ge::data.win.getSize() == sf::Vector2u(sf::VideoMode::getFullscreenModes()[0].width, sf::VideoMode::getFullscreenModes()[0].height)) {
            ge::createWindow(&ge::data, 1280, 720, "GhostKnight");
            player->healthRectY = 13;
            player->shieldRectY = 49;
            player->posXOffset = 0;
            player->isFullScreen = false;
        } else {
            ge::createFullScreenWindow(&ge::data, "GhostKnight");
            player->healthRectY = 13;
            player->shieldRectY = 69;
            player->posXOffset = 22;
            player->isFullScreen = true;
        }
       
    }
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
            ge::data.win.draw(j.sprite);
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
    player->update();
    weapons->update();
    updateViews();
    player->updateHealthBar();

}

void Game::render()
{
    map->render();
    if (!weapons->getWeapon(0)->held) 
        ge::data.win.draw(weapons->getWeapons()->begin()->weaponSprite);
    player->render();
    if (weapons->getWeapon(0)->held) 
        ge::data.win.draw(weapons->getWeapon(0)->weaponSprite);
    weapons->render();
}
