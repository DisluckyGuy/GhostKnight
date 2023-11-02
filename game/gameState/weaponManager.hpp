#pragma once
#include "../ge/ge.hpp"
#include <vector>

struct weaponStruct
{
    sf::Vector2f bulletVelocity;
    unsigned int firerate;
    unsigned int velocity;
    sf::Sprite weaponSprite;
    sf::Sprite bullet;
    std::vector<sf::Sprite> bullets;
    std::vector<sf::Vector2f> Velocities;
    sf::Clock elapsed;
    bool held;
};
class weaponManager {

    private:

    ge::Data* data;
    bool EHeld;

    
    
    weaponStruct rifle;
    std::vector<weaponStruct> weapons;


    void initVariables();
    void initWeapons();

    public:

    weaponManager(ge::Data* data);
    ~weaponManager();
    sf::Texture rifleTexture;
    std::vector<weaponStruct>* getWeapons();
    weaponStruct* getWeapon(unsigned int index);

    void shoot(weaponStruct* weapon, sf::Vector2f &mousePosView);
    void setFirerate(weaponStruct& weapon,unsigned int rate);
    void setWeaponTexture(weaponStruct& weapon, sf::Texture texture);
    void setBulletTexture(weaponStruct& weapon, sf::Texture texture);
    void setHold(weaponStruct weapon, bool isheld);

    void update();
};