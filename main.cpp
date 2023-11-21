#include "cppGameEngine\ge.hpp"
#include "game/gameState/Game.hpp"
#include "time.h"

using namespace ge;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    tools::toRadians(20);
    createWindow(&ge::data, 1280, 720, "temp");
    ge::read(&ge::data, "../.res/main.config");
    data.state.addState(new Game(&ge::data));
    Run(&ge::data);
    return 0;

}