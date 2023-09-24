#include "Game.hpp"

void Game::initVariables()
{
    for (int i = 0; i < mapStr.size(); i++) {
        if (i == 0 || i == 49) {
            mapStr[i] = "##################################################";
        } else {
            mapStr[i] = "#                                                #";
        }
    }
    if (!cellTexture.loadFromFile("C:/Mostafa/Code/C++/main/Files/testFiles/ParkourGame/gameTexture.png")) {
        cout << "couldn't load player and weapon texture" << endl;
    }
    pi = static_cast<float>(2 * acos(0.0));
}

void Game::initViews()
{
    mainView.reset(FloatRect(0,0,800,600));
}

void Game::initWindow()
{
    VM.width = 800;
    VM.height = 600;
    win = new RenderWindow(VM, "Game!", Style::Close | Style::Titlebar);
    win->setFramerateLimit(60);
    
}

void Game::initMap()
{
    wallCell.setTexture(cellTexture);
    wallCell.setTextureRect(IntRect(0,40,30,30));
    emptyCell.setTexture(cellTexture);
    emptyCell.setTextureRect(IntRect(30,40,30,30));
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.size(); j++) {
            if (mapStr[i][j] == '#') {
                wallCell.setPosition(static_cast<float>(i * 30), static_cast<float>(j * 30));
                map[i][j].second = Wall;
                map[i][j].first = wallCell;
            } else if (mapStr[i][j] == ' ') {
                emptyCell.setPosition(static_cast<float>(i * 30), static_cast<float>(j * 30));
                map[i][j].second = Empty;
                map[i][j].first = emptyCell;
            }
        }
    }
}

void Game::initBullets()
{
    fireRate = 100;
    bulletSpeed = 8;
    fireRateTimer = fireRateClock.getElapsedTime();
    bullet.setFillColor(Color::Yellow);
    bullet.setRadius(3);
}

Game::Game()
{
    initViews();
    initVariables();
    initWindow();
    initBullets();
    initMap();
}

Game::~Game()
{
    delete this->win;
}

const bool Game::isOpen()
{
    return win->isOpen();
}

void Game::pollEvents()
{
    while(win->pollEvent(event)) {
        switch(event.type) {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape) {
                    win->close();
                }
                break;
            case Event::Closed:
                win->close();
                break;
        }
    }
}

void Game::updateViews()
{
    mainView.setCenter(player.getPlayer()->getPosition().x + 15.f, player.getPlayer()->getPosition().y + 20.f);
    win->setView(mainView);
}

void Game::updateMousePos()
{
    mousePosWin = Mouse::getPosition(*win);
    mousePosView = win->mapPixelToCoords(mousePosWin);
}

void Game::checkCollisions()
{
    float velocity = player.getVelocity();
    Sprite* playerPtr = player.getPlayer();
    float playerSizeX = static_cast<float>(player.getPlayer()->getTextureRect().getSize().x);
    float playerSizeY = static_cast<float>(player.getPlayer()->getTextureRect().getSize().y);
    float wallSizeX = static_cast<float>(wallCell.getTextureRect().getSize().x);
    float wallSizeY = static_cast<float>(wallCell.getTextureRect().getSize().y);
    for (mapRow &i : map) {
        for (mapPair &j : i) {
            if (j.second == Wall) {
                if (j.first.getGlobalBounds().intersects(playerPtr->getGlobalBounds())) {
                    if (playerPtr->getPosition().y + playerSizeY < j.first.getPosition().y + wallSizeX && playerPtr->getPosition().y + playerSizeY > j.first.getPosition().y && playerPtr->getPosition().y < j.first.getPosition().y) {
                        playerPtr->move(0.f,-velocity);
                    }
                    if (playerPtr->getPosition().y - playerSizeY > j.first.getPosition().y - wallSizeY && playerPtr->getPosition().y < j.first.getPosition().y + wallSizeY && playerPtr->getPosition().y > j.first.getPosition().y) {
                        playerPtr->move(0.f,velocity);
                    }
                    if (playerPtr->getPosition().x + playerSizeX < j.first.getPosition().x + wallSizeX && playerPtr->getPosition().x + playerSizeX > j.first.getPosition().x && playerPtr->getPosition().x < j.first.getPosition().x) {
                        playerPtr->move(-velocity,0.f);
                    }
                    if (playerPtr->getPosition().x - playerSizeX > j.first.getPosition().x - wallSizeX && playerPtr->getPosition().x < j.first.getPosition().x + wallSizeX && playerPtr->getPosition().x > j.first.getPosition().x) {
                        playerPtr->move(velocity,0.f);
                    }
                } 
            }
        }
    }
}

void Game::setAngleAndSlope()
{
    double distX = (player.getPlayer()->getPosition().x + 15.f) - mousePosView.x;
    double distY = (player.getPlayer()->getPosition().y + 20.f) - mousePosView.y;
    slope = abs(distY / distX);
    angle = atan2(distY,distX) * 360 / (2*(2*acos(0.0)));
    angleR = atan2(distY,distX);
}

void Game::updateWeaponsGame()
{
    Sprite* weapon = player.getWeapon();
    if (player.getWeaponState() == Held) {
        player.getWeapon()->setRotation(static_cast<float>(angle + 180));
        if (angle <= 90.f && angle >= -90.f) {
            player.getWeapon()->setTextureRect(IntRect(40,70,40,18));
        } else {
            player.getWeapon()->setTextureRect(IntRect(0,70,40,18));
        }
    }
    if (angle <= 90.f && angle >= -90.f) {
        player.getPlayer()->setTextureRect(IntRect(30,0,30,40));
    } else {
        player.getPlayer()->setTextureRect(IntRect(0,0,30,40));
    }
}

void Game::renderMap()
{
    for (mapRow &i : map) {
        for (mapPair &j : i) {
            win->draw(j.first);
        }
    }
}

void Game::updateBullets()
{
    fireRateTimer = fireRateClock.getElapsedTime();
    int rate = fireRateTimer.asMilliseconds();
    Vector2f velocity;
    pair<CircleShape,Vector2f> bulletPair;
    if (Mouse::isButtonPressed(Mouse::Left) && player.getWeaponState() == Held) {
        if (rate > fireRate) {
            bullet.setPosition(player.getWeapon()->getPosition());
            if (angle > 90 || angle < -90) {
                velocity.x = static_cast<float>(bulletSpeed * -sin((angle + 85) * pi/180));
                velocity.y = static_cast<float>(bulletSpeed * cos((angle + 85) * pi/180));
            }
            else if (angle >= -90 || angle <= 90) {
                velocity.x = static_cast<float>(bulletSpeed * -sin((angle + 97) * pi/180)); 
                velocity.y = static_cast<float>(bulletSpeed * cos((angle + 97) * pi/180));
            }
            //velocity.y = static_cast<float>(bulletSpeed * cos((angle + 95) * pi/180));
            bullet.move(velocity.x * 4, velocity.y * 4);
            bulletPair.first = bullet;
            bulletPair.second = velocity;
            bullets.push_back(bulletPair); 
            fireRateClock.restart();
        }
    }
    for (pair<CircleShape,Vector2f> &i : bullets) {
        i.first.move(i.second);
    }
    for (int i = 0; i < bullets.size(); i++) {
        for (mapRow &j : map) {
           for (mapPair &k : j) {
                if (bullets[i].first.getGlobalBounds().intersects(k.first.getGlobalBounds()) && k.second == Wall) {
                    bullets.erase(bullets.begin() + i);
                }
            }
        }
    }
}

void Game::renderBullets()
{
    for (pair<CircleShape,Vector2f> &i : bullets) {
        win->draw(i.first);
    }
}

void Game::update()
{
    updateMousePos();
    player.update();
    checkCollisions();
    updateViews();
    setAngleAndSlope();
    updateWeaponsGame();
    updateBullets();
}

void Game::render()
{
    win->clear();
    renderMap();
    player.render(win);
    renderBullets();
    win->display();
}
