#pragma once

#include "resource.hpp"
#include "SFML/Graphics.hpp"

namespace ge
{
    class texture : public Resource<sf::Texture>{
        public:

        virtual void read(std::string path) {
            std::filebuf fb;

            if (!fb.open(path, std::ios::in)) {
                std::cout << " Error: couldn't open path: " << path << " " << std::endl;
                std::exit(-1);
            }

            std::istream is(&fb);
            sf::Image img;
            std::string tempName;
            std::vector<std::string> tempRect;
            bool multi = false;

            while(is) {
                std::string temp;
                std::getline(is,temp);

                if (temp.find(']') != std::string::npos) {
                    SpriteSheet(img, tempName, tempRect);
                    multi = false;
                    tempRect.clear();
                }

                if (temp.find(':') == std::string::npos && !multi) {continue;}

                std::string root = (path.find_last_of("/") == std::string::npos)? "" : path.substr(0,path.find_last_of('/') + 1);
                std::string first = temp.substr(0, temp.find(':'));
                std::string second = temp.substr(temp.find(':') + 2, temp.size() - 1);

                if (first == "spritesheet") {
                    read(root + second);
                }
                
                if (first == "mainTexture") {
                    if (!img.loadFromFile(root + second)) {
                        std::cout << "Error: couldn't load from path " << path << "." << std::endl;
                        std::exit(-1);
                    }
                }

                if (first == "playerTexture") {
                    if (!img.loadFromFile(root + second)) {
                        std::cout << "Error: couldn't load from path " << path << "." << std::endl;
                        std::exit(-1);
                    }
                }

                if (second == "[") {
                    multi = true;
                    tempName = first;
                    continue;
                }

                (multi)? tempRect.push_back(temp) : load(first, root + second);
            }

            fb.close();
        }

        void SpriteSheet(sf::Image &img, std::string &name, std::vector<std::string> &rect) {

            sf::Texture *tex = new sf::Texture[rect.size()];

            for (unsigned int i = 0; i < rect.size(); i++) {
                std::string temp = rect.at(i).substr(4, rect.at(i).size() - 1);

                
                int x = std::stoi(temp.substr(0, temp.find(' ')));

                temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                int y = std::stoi(temp.substr(0, temp.find(' ')));
                
                temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                int w = std::stoi(temp.substr(0, temp.find(' ')));

                temp = temp.substr(temp.find(' ') + 1, temp.size() - 1);
                int h = std::stoi(temp.substr(0, temp.find(' ')));

                

                sf::IntRect selection(x, y, w, h);

                if (!tex[i].loadFromImage(img, selection)) {
                    delete [] tex;
                    std::cout << "Error in loading " << name << " in iteration: " << i << std::endl;
                    std::exit(-1);
                }

                resources[name] = new ResourceObjArr<sf::Texture>(tex, rect.size());

            }
        }
    };
} // namespace ge
