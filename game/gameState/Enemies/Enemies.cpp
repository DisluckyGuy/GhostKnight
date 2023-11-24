#include "Enemies.hpp"

void Enemies::initSpawnTarget()
{
    spawnTarget.setTexture(enemyTexture);
    spawnTarget.setTextureRect(sf::IntRect(108,36,30,30));
    spawnTargets(maxTurrets, maxMonsters);
}

void Enemies::initTurret()
{
    maxTurrets = 6;
    turretBase.setTexture(enemyTexture);
    turretBase.setTextureRect(sf::IntRect(0,0,30,30));
    turretHead.setTexture(enemyTexture);
    turretHead.setTextureRect(sf::IntRect(30,0,24,17));
    turretBullet.setTexture(enemyTexture);
    turretBullet.setTextureRect(sf::IntRect(30,18,12,7));
    turret.init(turretBase, turretHead, turretBullet);
    //spawnTurrets(turret, maxTurrets);
}

void Enemies::initMonster()
{
    maxMonsters = 5;
    monsterSprite.setTexture(enemyTexture);
    monsterSprite.setTextureRect(sf::IntRect(55,0,42,36));
    monster.setSprite(monsterSprite);
    //spawnMonsters(monster, maxMonsters);
}

void Enemies::spawnTargets(int turretAmount, int monsterAmount)
{
    std::vector<sf::Vector2f> repeatedPos;
    repeatedPos.push_back(spawnTarget.getPosition());
    for (int i = 0; i < turretAmount; i++) {
        for (sf::Vector2f pos : repeatedPos) {
            do {
                spawnTarget.setPosition(30 + ((rand() % 48) * 30) ,30 + ((rand() % 48) * 30));
            } while (pos == spawnTarget.getPosition());
        }
        repeatedPos.push_back(spawnTarget.getPosition());
        enemySpawnTargets.push_back(spawnTarget);
    }
    for (int i = 0; i < monsterAmount; i++) {
        for (sf::Vector2f pos : repeatedPos) {
            do {
                spawnTarget.setPosition(30 + ((rand() % 48) * 30) ,30 + ((rand() % 48) * 30));
            } while (pos == spawnTarget.getPosition());
        }
        repeatedPos.push_back(spawnTarget.getPosition());
        enemySpawnTargets.push_back(spawnTarget);
    }
}

void Enemies::spawnTurrets(Turret &turret, int amount)
{
    //std::vector<sf::Vector2f> repeatedPos;
    //repeatedPos.push_back(turret.base.getPosition());
    for (int i = 0; i < amount; i++) {
        //for (sf::Vector2f pos : repeatedPos) {
        //    //do {
        //    //    turret.base.setPosition(30 + ((rand() % 48) * 30) ,30 + ((rand() % 48) * 30));
        //    //} while (pos == turret.base.getPosition());
        //}
        //repeatedPos.push_back(turret.base.getPosition());
        turret.base.setPosition(enemySpawnTargets[i].getPosition());
        turret.head.setPosition(turret.base.getPosition().x + turret.base.getGlobalBounds().width / 2, turret.base.getPosition().y + turret.base.getGlobalBounds().height / 2);
        turrets.push_back(turret);
    }
}

void Enemies::spawnMonsters(Monster &monster, int amount)
{
    //std::vector<sf::Vector2f> repeatedPos;
    //repeatedPos.push_back(monster.sprite.getPosition());
    for (int i = maxTurrets; i < amount + maxTurrets; i++) {
        //for (sf::Vector2f pos : repeatedPos) {
        //    do {
        //        monster.sprite.setPosition(30 + ((rand() % 48) * 30) ,30 + ((rand() % 48) * 30));
        //    } while (pos == monster.sprite.getPosition());
        //}
        monster.sprite.setPosition(enemySpawnTargets[i].getPosition());
        monsters.push_back(monster);
    }
}

Enemies::Enemies(weaponManager* weapons, Map* map, sf::Sprite* target) : turret(map, target), monster(map, target)
{
    this->map = map;
    this->weapons = weapons;
    this->target = target;
    enemyTexture = ge::data.texture.getResource("enemyTexture")[0];
    initTurret();
    initMonster();
    initSpawnTarget();
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

Monster *Enemies::getMonster(int index)
{
    return &monsters[index];
}

std::vector<Monster> *Enemies::getMonsters()
{
    return &monsters;
}

void Enemies::update()
{
    if (monsters.size() != 0 && turrets.size() != 0) {
        waveCooldown.restart();
    }
    if (waveCooldown.getElapsedTime().asMilliseconds() >= 3000) {
        spawnTurrets(turret, maxTurrets);
        spawnMonsters(monster, maxMonsters);
    }
    int aliveMonsters = maxMonsters;
    int aliveTurrets = maxTurrets;
    for (Turret &t : turrets) {
        t.update();
        if (!t.alive) {
            aliveTurrets -= 1;
        }
    }
    for (Monster &m : monsters) {
        m.update();
        if (!m.alive) {
            aliveMonsters -= 1;
        }
    }
    
    if (aliveTurrets <= 0 && aliveMonsters <= 0) {
        turrets.clear();
        monsters.clear();
        enemySpawnTargets.clear();
        spawnTargets(maxTurrets, maxMonsters);
    }
}

void Enemies::render()
{
    if (turrets.size() == 0 && monsters.size() == 0) {
        for (sf::Sprite sp : enemySpawnTargets) {
            ge::data.win.draw(sp);
        }
    }
    
    for (Turret &t : turrets) {
        t.render();
    }
    for (Monster &m : monsters) {
        m.render();
    }
}
