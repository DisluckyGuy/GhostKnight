#include <time.h>
#include <iostream>
#include "Game.hpp"

using namespace std;
int main()
{
    
    Game game;

    while (game.isOpen())
    {
        game.pollEvents();

        game.update();
        game.render();
    }
    
    return 0;
}