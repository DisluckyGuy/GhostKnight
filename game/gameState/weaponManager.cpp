#include "weaponManager.hpp"

void weaponManager::initWeapons()
{
    rifle.firerate = 200;
    rifle.weaponSprite.setPosition(100.f,100.f);
    rifleTexture.loadFromFile("game/ge/.res/img/mainTexture.png");
    rifle.weaponSprite.setTexture(rifleTexture);
    rifle.weaponSprite.setTextureRect(sf::IntRect(0,70,40,17));
    rifle.weaponSprite.setOrigin(8,8);
    weapons.push_back(rifle);
}

weaponManager::weaponManager(ge::Data *data)
{
    this->data = data;
    initWeapons();
}

weaponManager::~weaponManager()
{
    delete this->data;
}
std::vector<weaponStruct> *weaponManager::getWeapons()
{
    return &weapons;
}

weaponStruct *weaponManager::getWeapon(unsigned int index)
{
    return &weapons[index];
}

void weaponManager::shoot(weaponStruct& weapon, sf::Vector2f &mousePosView)
{
    if (weapon.elapsed.getElapsedTime().asMilliseconds() >= weapon.firerate) {
        weapon.elapsed.restart();
        weapon.bullet.setPosition(weapon.weaponSprite.getPosition());
        weapon.bullets.push_back(weapon.bullet);
    }
}

void weaponManager::setFirerate(weaponStruct& weapon,unsigned int rate)
{
    weapon.firerate = rate;
}

void weaponManager::setWeaponTexture(weaponStruct& weapon,sf::Texture texture)
{
    weapon.weaponSprite.setTexture(texture);
}

void weaponManager::setBulletTexture(weaponStruct& weapon,sf::Texture texture)
{
    weapon.bullet.setTexture(texture);
}

void weaponManager::setHold(weaponStruct weapon,bool isHeld)
{
    weapon.held = isHeld;
}
