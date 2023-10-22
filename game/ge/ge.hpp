#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "state/state.hpp"
#include "resource/resource.hpp"
#include "resource/texture.hpp"
#include "tools/tools.hpp"

namespace ge {
    struct Data
    {
        sf::RenderWindow win;
        sf::Event ev;
        sf::Clock clock;
        unsigned int width;
        unsigned int height;
        state::Handler state;
        texture texture;
        Resource<sf::Font> font;
    };
    
    inline void createWindow(Data* data, unsigned int width, unsigned int height, std::string title) {
        data->width = width;
        data->height = height;
        data->win.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
        data->win.setFramerateLimit(60);
    }

    inline void read(Data* data, std::string path) {
        std::filebuf fb;
        if (!fb.open(path, std::ios::in)) {
            std::cout << " Error: couldn't open path: " << path << " " << std::endl;
            std::exit(-1);
        }
        std::istream is(&fb);
        while(is) {
            std::string temp;
            std::getline(is,temp);
            if (temp.find(':') == std::string::npos) {continue;}
            std::string root = path.substr(0,path.find_last_of('/') + 1);
            std::string first = temp.substr(0, temp.find(':'));
            std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);
            if (first == "texture") {
                data->texture.read(root + second);
            } else if (first == "font") {
                data->font.read(root + second);
            }
        }
        fb.close();
    }

    inline void Run(Data* data) {
        //update
        float dt = data->clock.getElapsedTime().asSeconds();
        float new_dt = 0.0f, elapsed = 0.0f;
        
        while (data->win.isOpen()){
            while(data->win.pollEvent(data->ev)){
                if(data->ev.type == sf::Event::Closed){
                    data->win.close();
                }
            }

            data->state.update();
            
            data->win.clear();
            data->state.render();
            data->win.display();
        }
    } 
}