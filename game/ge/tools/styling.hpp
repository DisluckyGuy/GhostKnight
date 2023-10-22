#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace ge
{
    namespace tools {
        
        inline sf::IntRect flipTextureX(sf::Sprite s) {
            sf::IntRect textureBounds = s.getTextureRect();
            sf::IntRect flippedTexture = sf::IntRect(textureBounds.getPosition().x + textureBounds.width, textureBounds.getPosition().y, -textureBounds.width, textureBounds.height);
            return flippedTexture;
        }

        inline sf::IntRect flipTextureX(sf::IntRect rect) {
            sf::IntRect flippedTexture = sf::IntRect(rect.getPosition().x + rect.width, rect.getPosition().y, -rect.width, rect.height);
            return flippedTexture;
        }

        inline sf::IntRect flipTextureY(sf::Sprite s) {
            sf::IntRect textureBounds = s.getTextureRect();
            sf::IntRect flippedTexture = sf::IntRect(textureBounds.getPosition().x, textureBounds.getPosition().y + textureBounds.height, textureBounds.width, -textureBounds.height);
            return flippedTexture;
        }

        inline sf::IntRect flipTextureY(sf::IntRect rect) {
            sf::IntRect flippedTexture = sf::IntRect(rect.getPosition().x, rect.getPosition().y + rect.height, rect.width, -rect.height);
            return flippedTexture;
        }

    }
} // namespace ge
