#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>

struct Frame {
        int duration;
        sf::IntRect rect;
};
class Animation
{
private:
    
    sf::Clock clock;
    sf::Sprite* sprite;
    Frame animationFrame;
    std::vector<Frame> animationFrames;
    int currentFrame = 0;
    
public:

    void setSprite(sf::Sprite* sprite) {
        this->sprite = sprite;
    }

    void addFrame(sf::IntRect rect, int duration) {
        animationFrame.duration = duration;
        animationFrame.rect = rect;
        animationFrames.push_back(animationFrame);
    }

    int getCurrentFrame() {
        return currentFrame;
    }
    
    void setFrame(int index) {
        currentFrame = index;
    }

    sf::IntRect getFrame() {
        return animationFrames[currentFrame].rect;
    }

    void play() {
        if (animationFrames.size() == 0) {
            return;
        }
        if (clock.getElapsedTime().asMilliseconds() >= animationFrames[currentFrame].duration && currentFrame == animationFrames.size() - 1) {
            currentFrame = 0;
            clock.restart();
        }
        if (clock.getElapsedTime().asMilliseconds() >= animationFrames[currentFrame].duration) {
            currentFrame += 1;
            clock.restart();
        }
        sprite->setTextureRect(animationFrames[currentFrame].rect);
        //std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
        //std::cout << currentFrame << std::endl;
        
        
    }

    ~Animation() {
        delete this->sprite;
    }

};
