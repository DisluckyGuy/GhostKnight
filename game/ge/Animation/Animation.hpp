#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "../tools/tools.hpp"

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

    ~Animation() {
        delete this->sprite;
    }

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

    void reset() {
        clock.restart();
        currentFrame = 1;
    }

    sf::IntRect getFrame() {
        return animationFrames[currentFrame].rect;
    }

    void play(bool flip = false) {
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
        if (flip) {
            sprite->setTextureRect(ge::tools::flipTextureX(animationFrames[currentFrame].rect));
        } else {
            sprite->setTextureRect(animationFrames[currentFrame].rect);
        } 
    }

};
