#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cmath>

namespace ge {
    namespace tools {

        inline float Pi = 2 * std::acos(0.0);

        inline float findSlope(sf::Sprite s1, sf::Sprite s2) {
            float distX = std::abs(s2.getPosition().x - s1.getPosition().x);
            float distY = std::abs(s2.getPosition().y - s1.getPosition().y);
            float slope = distY / distX;
            return slope;
        }

        inline float findSlope(sf::Vector2f v1, sf::Vector2f v2) {
            float distX = std::abs(v2.x - v1.x);
            float distY = std::abs(v2.y - v1.y);
            float slope = distY / distX;
            return slope;
        }

        inline float findSlope(sf::Vector2i v1, sf::Vector2i v2) {
            float distX = std::abs(v2.x - static_cast<float>(v1.x));
            float distY = std::abs(v2.y - static_cast<float>(v1.y));
            float slope = distY / distX;
            return slope;
        }
        
    }
}