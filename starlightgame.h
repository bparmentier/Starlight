#ifndef STARLIGHTGAME_H
#define STARLIGHTGAME_H

#include <string>

#include "starlight/level.h"
#include "o_sdo/sujetdobservation.h"

/*!
 * \brief The StarlightGame class
 */
class StarlightGame
{
    nvs::Level *m_level;

public:

    /*!
     * \brief Construit un StarlightGame
     * \param fileName
     */
    StarlightGame(const std::string &fileName);

    ~StarlightGame();

    /*!
     * \brief Lit le contenu du fichier de carte donné par *fileName* et crée un
     * nouveau nvs::Level
     * \param fileName le chemin vers le fichier de carte
     */
    void readMap(const std::string &fileName);

    /*!
     * \brief Retourne le nvs::Level du jeu
     * \return le nvs::Level
     */
    nvs::Level * getLevel();
};

#endif // STARLIGHTGAME_H
