#include "Enemies.hpp"

void Enemies::initTurret()
{
    maxTurrets = 6;
    enemyTexture = ge::data.texture.getResource("enemyTexture")[0];
    turretBase.setTexture(enemyTexture);
    turretBase.setTextureRect(sf::IntRect(0,0,30,30));
    turretHead.setTexture(enemyTexture);
    turretHead.setTextureRect(sf::IntRect(30,0,24,17));
    turretBullet.setTexture(enemyTexture);
    turretBullet.setTextureRect(sf::IntRect(30,18,12,7));
    turret.init(turretBase, turretHead, turretBullet);
    spawnTurrets(turret, maxTurrets);
}

void Enemies::spawnTurrets(Turret &turret, int amount)
{
    std::vector<sf::Vector2f> repeatedPos;
    repeatedPos.push_back(turret.base.getPosition());
    for (int i = 0; i < amount; i++) {
        for (sf::Vector2f pos : repeatedPos) {
            do {
                turret.base.setPosition(30 + ((rand() % 48) * 30) ,30 + ((rand() % 48) * 30));
            } while (pos == turret.base.getPosition());
        }
        repeatedPos.push_back(turret.base.getPosition());
        turret.head.setPosition(turret.base.getPosition().x + turret.base.getGlobalBounds().width / 2, turret.base.getPosition().y + turret.base.getGlobalBounds().height / 2);
        turrets.push_back(turret);
    }
}

Enemies::Enemies(weaponManager* weapons, Map* map, sf::Sprite* target) : turret(map, target)
{
    this->map = map;
    this->weapons = weapons;
    this->target = target;
    initTurret();
}

void Enemies::setTarget(sf::Sprite *target)
{
    this->target = target;
}

Turret* Enemies::getTurret(int index)
{
    return &turrets[index];
}

std::vector<Turret>* Enemies::getTurrets()
{
    return &turrets;
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
