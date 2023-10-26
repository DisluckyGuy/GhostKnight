#pragma once
#include "../ge/ge.hpp"
#include <vector>

struct weaponStruct
{
    unsigned int firerate;
    sf::Sprite weaponSprite;
    sf::Sprite bullet;
    std::vector<sf::Sprite> bullets;
    sf::Clock elapsed;
    bool held;
};
class weaponManager {

    private:

    ge::Data* data;

    
    
    weaponStruct rifle;
    std::vector<weaponStruct> weapons;
    
    void initWeapons();

    public:

    weaponManager(ge::Data* data);
    ~weaponManager();
    sf::Texture rifleTexture;
    std::vector<weaponStruct>* getWeapons();
    weaponStruct* getWeapon(unsigned int index);

    void shoot(weaponStruct& weapon, sf::Vector2f &mousePosView);
    void setFirerate(weaponStruct& weapon,unsigned int rate);
    void setWeaponTexture(weaponStruct& weapon, sf::Texture texture);
    void setBulletTexture(weaponStruct& weapon, sf::Texture texture);
    void setHold(weaponStruct weapon, bool isheld);

};