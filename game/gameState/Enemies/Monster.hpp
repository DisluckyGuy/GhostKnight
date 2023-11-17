#pragma once

#include <vector>
#include <iostream>
#include "../../ge/ge.hpp"
#include "../weaponManager.hpp"
#include "../map.hpp"

class Monster {

    private:

    Map* map;

    public:

    Monster(ge::Data* data, Map* map);

};