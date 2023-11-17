#include "game\ge\ge.hpp"
#include "game\game.hpp"
#include "game/gameState/Game.hpp"
#include "time.h"

using namespace ge;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    Data *data = new ge::Data;
    tools::toRadians(20);
    createWindow(data, 1650, 1050, "temp");
    ge::read(data, "game/ge/.res/main.config");
    data->state.addState(new Game(data));
    Run(data);
    return 0;

}