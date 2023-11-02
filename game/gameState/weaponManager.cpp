#include "weaponManager.hpp"

void weaponManager::initVariables()
{
    EHeld = false;
}

void weaponManager::initWeapons()
{
    rifle.firerate = 200;
    rifle.weaponSprite.setPosition(100.f,100.f);
    rifle.weaponSprite.setTexture(data->texture.getResource("mainTexture")[0]);
    rifle.weaponSprite.setTextureRect(sf::IntRect(0,70,40,17));
    rifle.bullet.setTexture(data->texture.getResource("mainTexture")[0]);
    rifle.bullet.setTextureRect(sf::IntRect(0,119,7,4));
    rifle.weaponSprite.setOrigin(8,9);
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

void weaponManager::shoot(weaponStruct* weapon, sf::Vector2f &mousePosView)
{
    if (weapon->elapsed.getElapsedTime().asMilliseconds() >= weapon->firerate) {
        weapon->elapsed.restart();
        weapon->bullet.setRotation(weapon->weaponSprite.getRotation());
        weapon->bullet.setPosition(weapon->weaponSprite.getPosition());
        float VelocityX = ge::tools::findVelocity(ge::tools::toRadians(ge::tools::findAngle(weapon->weaponSprite, mousePosView)), 5).x;
        float VelocityY = ge::tools::findVelocity(ge::tools::toRadians(ge::tools::findAngle(weapon->weaponSprite, mousePosView)), 5).y;
        weapon->Velocities.push_back(sf::Vector2f(VelocityX, VelocityY));
        weapon->bullets.push_back(weapon->bullet);
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

void weaponManager::update()
{
    for (weaponStruct &weapon : weapons) {
        if (weapon.held) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && weapon.held) {
                sf::Vector2f MPV = ge::getMousePosView(data);
                shoot(&weapon, MPV);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if (!EHeld) {
                EHeld = true;
            }
        } else {
            EHeld = false;
        }
        for (weaponStruct &weapon : weapons) {
            for (int i = 0; i < weapon.bullets.size(); i++) {
                weapon.bullets[i].move(weapon.Velocities[i]);
            }
        }
    }
}