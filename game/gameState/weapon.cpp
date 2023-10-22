#include "weapon.hpp"

weapon::weapon(ge::Data *data)
{
    this->data = data;
}

weapon::~weapon()
{
    delete this->data;
}

sf::Sprite *weapon::getSprite()
{
    return &weaponSprite;
}

bool weapon::getState()
{
    return held;
}

void weapon::shoot(sf::Vector2f &mousePosView)
{
    if (elapsed.getElapsedTime().asMilliseconds() >= firerate) {
        std::cout << "shot" << std::endl;
        elapsed.restart();
        bullet.setPosition(weaponSprite.getPosition());
        bullets.push_back(bullet);
    }
}

void weapon::setFirerate(unsigned int rate)
{
    firerate = rate;
}

void weapon::setWeaponTexture(sf::Texture texture)
{
    weaponSprite.setTexture(texture);
}

void weapon::setBulletTexture(sf::Texture texture)
{
    bullet.setTexture(texture);
}

void weapon::setHold(bool isHeld)
{
    held = isHeld;
}
