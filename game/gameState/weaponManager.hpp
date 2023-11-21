#pragma once
#include "../../cppGameEngine/ge.hpp"
#include <vector>
#include "map.hpp"

struct weaponStruct
{
    float angle;
    float bulletSpeed;
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

    public:

    weaponManager(Map* map);
    ~weaponManager();
    sf::Texture rifleTexture;

    std::vector<weaponStruct>* getWeapons();
    weaponStruct* getWeapon(unsigned int index);
    std::vector<sf::Sprite>* getBullets(int index);

    void shoot(weaponStruct* weapon, sf::Vector2f &mousePosView);
    void setFirerate(weaponStruct& weapon,unsigned int rate);
    void setWeaponTexture(weaponStruct& weapon, sf::Texture texture);
    void setBulletTexture(weaponStruct& weapon, sf::Texture texture);
    void setHold(weaponStruct weapon, bool isheld);

    void updateWeaponAngle(weaponStruct &weapon);
    void updateWeaponState(weaponStruct &weapon);
    void updateBulletCollisions(weaponStruct &weapon);

    void update();
    void render();

    private:

    Map* map;
    bool EHeld;

    
    
    weaponStruct rifle;
    std::vector<weaponStruct> weapons;


    void initVariables();
    void initWeapons();

};