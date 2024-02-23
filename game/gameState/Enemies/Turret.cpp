#include "Turret.hpp"

void Turret::changeHealth(int change)
{
    health += change;
}

void Turret::updateHead(sf::Sprite *target)
{
    float angle = ge::tools::findAngle(head, *target);
    head.setRotation(angle);
    sf::Vector2f basePos = base.getPosition();
    head.setPosition(basePos.x + roundf(base.getGlobalBounds().width / 2),basePos.y + roundf(base.getGlobalBounds().height / 2));
}

void Turret::updateBullets()
{
    
    for (std::array<Cell,50> &row : *map->getMap()) {
        for (Cell &cell : row) {
            if (cell.type == cellType::Wall) {
                for (int i = 0; i < bullets.size(); i++) {
                    if (cell.sprite.getGlobalBounds().intersects(bullets[i].sprite.getGlobalBounds())) {
                        bullets.erase(bullets.begin() + i);
                    }
                }
                
            }
        }
    }
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].sprite.getGlobalBounds().intersects(target->getGlobalBounds())) {
            bullets.erase(bullets.begin() + i);
        }
        bullets[i].sprite.move(bullets[i].velocity);
    }
}

Turret::Turret(Map *map, sf::Sprite* target)
{
    this->map = map;
    this->target = target;
    health = 10;
    fireRate = 200;
    bulletVelocity = 6;
    distanceMin = 500;
    alive = true;
}

Turret::~Turret()
{
}

void Turret::init(sf::Sprite base, sf::Sprite head, sf::Sprite bullet)
{
    this->base = base;
    this->head = head;
    this->bullet.sprite = bullet;
    this->head.setOrigin(roundf(head.getGlobalBounds().width / 2),roundf(head.getGlobalBounds().height / 2));
}

void Turret::shoot()
{
    if (fireClock.getElapsedTime().asMilliseconds() >= fireRate) {
        sf::Vector2f center = sf::Vector2f(target->getPosition().x + target->getGlobalBounds().width / 2, target->getPosition().y + target->getGlobalBounds().height / 2);
        float angle = ge::tools::findAngle(head, center);
        sf::Vector2f velocity = ge::tools::findVelocity(ge::tools::toRadians(angle), bulletVelocity);
        bullet.sprite.setPosition(head.getPosition().x + velocity.x * 2, head.getPosition().y + velocity.y * 2);
        bullet.sprite.setRotation(angle);
        bullet.velocity = velocity;
        bullets.push_back(bullet);
        fireClock.restart();
    }
}

void Turret::update()
{
    updateBullets();
    if (!alive) {
        return;
    }
    updateHead(target);
    distX = abs(target->getPosition().x - head.getPosition().x);
    distY = abs(target->getPosition().y - head.getPosition().y);
    if (distX < distanceMin && distY < distanceMin) {
        shoot();
    }
    if (health <= 0) {
        alive = false;
        head.setTextureRect(sf::IntRect(84,36,24,17));
    }
}

void Turret::render()
{
    ge::data.win.draw(base);
    ge::data.win.draw(head);
    for (Bullet &b : bullets) {
        ge::data.win.draw(b.sprite);
    }
}
