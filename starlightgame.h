#ifndef STARLIGHTGAME_H
#define STARLIGHTGAME_H

#include <string>

#include "starlight/level.h"
#include "o_sdo/sujetdobservation.h"

class StarlightGame
{
    nvs::Level * m_level;

public:

    StarlightGame(const std::string & fileName);
    ~StarlightGame();
    void readMap(const std::string & fileName);
    nvs::Level * getLevel();
};

#endif // STARLIGHTGAME_H
