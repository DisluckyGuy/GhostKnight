#pragma once
#include "../ge/ge.hpp"
#include <vector>

class weapon {

    private:

    bool held;
    ge::Data* data;
    unsigned int firerate;
    sf::Sprite weaponSprite;
    sf::Sprite bullet;
    std::vector<sf::Sprite> bullets;
    sf::Clock elapsed;

    public:

    weapon(ge::Data* data);
    ~weapon();

    sf::Sprite* getSprite();
    bool getState();

    void shoot(sf::Vector2f &mousePosView);
    void setFirerate(unsigned int rate);
    void setWeaponTexture(sf::Texture texture);
    void setBulletTexture(sf::Texture texture);
    void setHold(bool isheld);

};