#include "cppGameEngine\ge.hpp"
#include "game/gameState/Game.hpp"
#include "time.h"

using namespace ge;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    //Data *data = new ge::Data;
    tools::toRadians(20);
    createWindow(&ge::data, 1650, 1050, "temp");
    ge::read(&ge::data, "cppGameEngine/.res/main.config");
    data.state.addState(new Game(&ge::data));
    Run(&ge::data);
    //delete ge::data;
    return 0;

}