#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "geometry.hpp"
 
namespace ge
{
    namespace tools {
        
        inline float toRadians(float degree) {
            return degree * (Pi/180);
        }

        inline float toDegrees(float radian) {
            return radian * (180/Pi);
        }

        inline float findAngle(sf::Sprite &s1, sf::Sprite &s2) {
            float distX = std::abs(s2.getPosition().x - s1.getPosition().x);
            float distY = std::abs(s2.getPosition().y - s1.getPosition().y);
            float angle = atan2f(distY, distX) * 180/Pi;
            return angle;
        }

        inline float findAngle(sf::Vector2f &v1, sf::Vector2f *v2) {
            float distX = std::abs(v2->x - v1.x);
            float distY = std::abs(v2->y - v1.y);
            float angle = atan2f(distY, distX) * 180/Pi;
            return angle;
        }

        inline float findAngle(sf::Sprite &s1, sf::Vector2i &v2) {
            float distX = static_cast<float>(v2.x) - s1.getPosition().x;
            float distY = static_cast<float>(v2.y) - s1.getPosition().y;
            float angle = atan2f(distY, distX) * 180/Pi;
            return angle;
        }

        inline float findAngle(sf::Sprite &s1, sf::Vector2f &v2) {
            float distX = v2.x - s1.getPosition().x;
            float distY = v2.y - s1.getPosition().y;
            float angle = std::atan2(distY, distX) * 180/Pi;
            return angle;
        }

        inline sf::Vector2f findVelocity(float radian, float velocity = 1) {
            float velocityX  = velocity * std::cos(radian);
            float velocityY  = velocity * std::sin(radian);
            return sf::Vector2f(velocityX,velocityY);
        }
    }
} // namespace ge
