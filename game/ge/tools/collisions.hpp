#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

namespace ge {
    namespace tools {
        inline void isColliding(sf::Sprite &s1, sf::Sprite &s2, float velocity) {
            sf::FloatRect s1bounds = s1.getGlobalBounds();
            sf::FloatRect s2bounds = s2.getGlobalBounds();
            if (s1bounds.intersects(s2bounds)) {
                if (s1bounds.left < s2bounds.left + s2bounds.width && s1bounds.left > s2bounds.left && s1bounds.left + s1bounds.width > s2bounds.left + s2bounds.width) {
                    s1.move(velocity,0.f);
                }
                if (s1bounds.left + s1bounds.width > s2bounds.left && s1bounds.left < s2bounds.left && s1bounds.left + s1bounds.width < s2bounds.left + s2bounds.width) {
                    s1.move(-velocity,0.f);
                }
                if (s1bounds.top < s2bounds.top + s2bounds.height && s1bounds.top > s2bounds.top && s1bounds.top + s1bounds.height > s2bounds.top + s2bounds.height) {
                    s1.move(0.f,velocity);
                }
                if (s1bounds.top + s1bounds.height < s2bounds.top && s1bounds.top < s2bounds.top && s1bounds.top + s1bounds.height < s2bounds.top + s2bounds.height) {
                    s1.move(0.f,-velocity);
                }
            }
        }

        inline bool isColliding(sf::Sprite &s1, sf::Sprite &s2) {
            sf::FloatRect s1bounds = s1.getGlobalBounds();
            sf::FloatRect s2bounds = s2.getGlobalBounds();
            if (
            (s1bounds.left < s2bounds.left + s2bounds.width && s1bounds.left > s2bounds.left && s1bounds.left + s1bounds.width > s2bounds.left + s2bounds.width) || 
            (s1bounds.left + s1bounds.width > s2bounds.left && s1bounds.left < s2bounds.left && s1bounds.left + s1bounds.width < s2bounds.left + s2bounds.width) || 
            (s1bounds.top < s2bounds.top + s2bounds.height && s1bounds.top > s2bounds.top && s1bounds.top + s1bounds.height > s2bounds.top + s2bounds.height) || 
            (s1bounds.top + s1bounds.height < s2bounds.top && s1bounds.top < s2bounds.top && s1bounds.top + s1bounds.height < s2bounds.top + s2bounds.height)
            ) {
                return true;
            } else {
                return false;
            }
        }

        inline bool isColliding(sf::Vector2f p, sf::Sprite &s2) {
            sf::FloatRect s2bounds = s2.getGlobalBounds();
            if (s2bounds.contains(p)) {
                return true;
            } else {
                return false;
            }
        }
    }
}