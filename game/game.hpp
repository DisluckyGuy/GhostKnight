#pragma once 
#include "ge/ge.hpp"
class game : public ge::State{
    public:
    game(ge::Data *data): ge::State(data){
        tempSprite.setTexture(data->texture.getResource("ssimg")[0]);
        sf::IntRect ft = ge::tools::flipTextureY(tempSprite);
        tempSprite.setTextureRect(ft);
    }

    void update(){}
    void render(){data->win.draw(tempSprite);};
private:

    sf::Sprite tempSprite;

};