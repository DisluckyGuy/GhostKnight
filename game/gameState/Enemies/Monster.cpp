#include "Monster.hpp"

Monster::Monster(Map* map, sf::Sprite *target)
{
    this->map = map;
    this->target = target;
    velocity = sf::Vector2f(0,0);
    alive = true;
    speed = 1;
    health = 20 ;
    mode = MonsterMode::Wander;
    minFollowDistance = sf::Vector2f(400.f,300.f);
    minAttackDistance = sf::Vector2f(100.f,100.f);
    isAttacking = false;
    tempTexture = ge::data.texture.getResource("enemyTexture")[0];
    sprite.setTexture(tempTexture);
    animation.setSprite(&sprite);
}

void Monster::changeHealth(int amount)
{
    health += amount;
}

void Monster::setSprite(sf::Sprite sprite)
{
    this->sprite = sprite;
    flippedRect = ge::tools::flipTextureX(sprite);
    mainRect = sprite.getTextureRect();
    animation.addFrame(sf::IntRect(mainRect), 100);
    animation.addFrame(sf::IntRect(0,36,42,36), 100);
    
}

void Monster::attack(float angle, sf::Vector2f velocity)
{
    sprite.move(velocity);
}

void Monster::updateAngle()
{
    
    if (isAttacking) {
        sprite.setRotation(angle);
        return;
    }

    sprite.setRotation(0);
    animation.setSprite(&sprite);
    if ((angle > -90 && angle < 0) || (angle < 90 && angle > 0)) {
        animation.play(true);
    } else {
        animation.play();
    }
}

void Monster::updateMode()
{
    if ((distance.x < minFollowDistance.x && distance.y < minFollowDistance.y) && (distance.x >= minAttackDistance.x && distance.y >= minAttackDistance.y) && !isAttacking) {
        mode = MonsterMode::Follow;
    } else if (distance.x < minAttackDistance.x && distance.y < minAttackDistance.y) {
        mode = MonsterMode::Attack;
    } else if (distance.x > minFollowDistance.x && distance.y > minFollowDistance.y && !isAttacking){
        mode = MonsterMode::Wander;
    }
    updateWander();
    updateFollow();
    updateAttack();
    if (health == 0) {
        alive = false;
        sprite.setTextureRect(sf::IntRect(42,36,42,36));
    }
}

void Monster::updateWander()
{
    if (mode != MonsterMode::Wander) {
        return;
        wanderClock.restart();
    }
    if (wanderClock.getElapsedTime().asMilliseconds() >= 1000) {
        angle = (rand() % 360) - 180;
        velocity = ge::tools::findVelocity(ge::tools::toRadians(angle), speed);
        wanderClock.restart();
    }
    sprite.move(velocity);
}

void Monster::updateFollow()
{
    if (mode != MonsterMode::Follow) {
        return;
    }
    angle = ge::tools::findAngle(sprite, *target);
    velocity = ge::tools::findVelocity(ge::tools::toRadians(angle), speed);
    sprite.move(velocity);
}

void Monster::updateAttack()
{
    if (mode != MonsterMode::Attack) {
        attackClock.restart();
        return;
    }
    
    if (!isAttacking) {
        sf::Vector2f center =  sf::Vector2f(target->getPosition().x + target->getGlobalBounds().width / 2, target->getPosition().y + target->getGlobalBounds().height / 2);
        angle = ge::tools::findAngle(sprite, center);
        velocity = ge::tools::findVelocity(ge::tools::toRadians(angle), 5);
        if ((angle > -90 && angle < 0) || (angle < 90 && angle > 0)) {
            sprite.setTextureRect(sf::IntRect(97,0,60,31));
        } else {
            sprite.setTextureRect(sf::IntRect(97,31,60,-31));
        }
            
    }

    isAttacking = true;
    
    attack(angle ,velocity);


    if (attackClock.getElapsedTime().asMilliseconds() >= 1500) {
        sprite.setTextureRect(mainRect);
        isAttacking = false;
        mode = MonsterMode::Wander;
    }
}
  
void Monster::update() 
{
    if (!alive) {
        return;
    }
    distance = sf::Vector2f(std::abs(target->getPosition().x - sprite.getPosition().x),std::abs(target->getPosition().y - sprite.getPosition().y));
    checkCollisions();
    updateAngle();
    updateMode();
}

void Monster::render()
{
    ge::data.win.draw(sprite);
}

void Monster::checkCollisions()
{
    for (std::array<Cell,50> &row : *map->getMap()) {
        for (Cell &cell : row) {
            if (cell.type == cellType::Wall) {
                if (isAttacking) {
                    ge::tools::isColliding(sprite, cell.sprite, 5);
                    continue;
                }
                ge::tools::isColliding(sprite, cell.sprite, speed);
            }
        }
    }
}
