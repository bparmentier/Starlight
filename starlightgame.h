#ifndef STARLIGHTGAME_H
#define STARLIGHTGAME_H

#include <string>

#include "starlight/level.h"
#include "o_sdo/sujetdobservation.h"

class StarlightGame
{
    nvs::Level * m_level;

public:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    StarlightGame(const std::string & nomFichier);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    ~StarlightGame();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void lireMap(const std::string & nomFichier);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    nvs::Level * getLevel();
};

#endif // STARLIGHTGAME_H
