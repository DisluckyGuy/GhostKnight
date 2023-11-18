#include "Enemies.hpp"

void Enemies::initTurret()
{
    maxTurrets = 7;
    enemyTexture = data->texture.getResource("enemyTexture")[0];
    turretBase.setTexture(enemyTexture);
    turretBase.setTextureRect(sf::IntRect(0,0,30,30));
    turretHead.setTexture(enemyTexture);
    turretHead.setTextureRect(sf::IntRect(30,0,24,17));
    turretBullet.setTexture(enemyTexture);
    turretBullet.setTextureRect(sf::IntRect(30,18,12,7));
    turret.init(turretBase, turretHead, turretBullet);
    for (int i = 0; i < 1; i++) {
        turret.base.setPosition(30 + ((rand() % 48) * 30) ,30 + ((rand() % 48) * 30));
        turret.head.setPosition(turret.base.getPosition().x + turret.base.getGlobalBounds().width / 2, turret.base.getPosition().y + turret.base.getGlobalBounds().height / 2);
        turrets.push_back(turret);
    }
}

Enemies::Enemies(ge::Data* data, weaponManager* weapons, Map* map, sf::Sprite* target) : turret(data, map, target)
{
    
    this->data = data;
    this->map = map;
    this->weapons = weapons;
    this->target = target;
    initTurret();
}

void Enemies::setTarget(sf::Sprite *target)
{
    this->target = target;
}

void Enemies::update()
{
    if (turrets.size() == 0) {
        return;
    }
    for (Turret &t : turrets) {
        t.update();
    }
}

void Enemies::render()
{
    if (turrets.size() == 0) {
        return;
    }
    for (Turret &t : turrets) {
        t.render();
    }
}
