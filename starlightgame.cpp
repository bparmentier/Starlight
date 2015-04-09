#include "starlightgame.h"
#include <iostream>
#include <fstream>

using namespace std;

StarlightGame::StarlightGame(const string & nomFichier)
{
    lireMap(nomFichier);
}

StarlightGame::~StarlightGame()
{
    delete m_level;
    m_level = nullptr;
}

void StarlightGame::lireMap(const string & nomFichier)
{
    ifstream fichier{nomFichier};
    char element;
    int largeurMap, hauteurMap, longueur_onde, mod, lomin, lomax;
    double x, y, x1, x2, y1, y2, largeur, hauteur, longueur, bord, rad, alpha;

    vector<nvs::Crystal> tabCristaux;
    vector<nvs::Wall> tabMurs;
    vector<nvs::Lens> tabLentilles;
    vector<nvs::Mirror> tabMiroires;
    vector<nvs::Bomb> tabBombes;
    nvs::SourceOfLight source;
    nvs::Target destination;

    if (!fichier.is_open()) {
        string msg { "Fichier : \"" };
        msg += nomFichier;
        msg += "\" introuvable.";
        throw msg;
    }

    /* first line: width and height */
    fichier >> largeurMap >> hauteurMap;

    /* map components */
    while (fichier >> element) {
        switch (element) {
        case 'S':
            fichier >> x >> y >> bord >> alpha >> longueur_onde;
            source = nvs::SourceOfLight {x,y,bord,alpha,longueur_onde};
            break;
        case 'D':
            fichier >> x >> y >> bord;
            destination = nvs::Target {x,y,bord};
            break;
        case 'C':
            fichier >> x >> y >> rad >> mod;
            tabCristaux.push_back(nvs::Crystal{x,y,rad,mod});
            break;
        case 'L':
            fichier >> x >> y >> largeur >> hauteur >> lomin >> lomax;
            tabLentilles.push_back(nvs::Lens{x,y,largeur,hauteur,lomax,lomin});
            break;
        case 'W':
            fichier >> x1 >> y1 >> x2 >> y2;
            tabMurs.push_back(nvs::Wall{x1,y1,x2,y2});
            break;
        case 'N':
            fichier >> x >> y >> rad;
            tabBombes.push_back(nvs::Bomb{x,y,rad});
            break;
        case 'M':
            fichier >> x >> y >> longueur >> alpha;
            tabMiroires.push_back(nvs::Mirror{x,y,longueur,alpha});
            break;
        }
    }
    m_level = new nvs::Level{largeurMap,hauteurMap,source,destination,
            tabMurs,tabMiroires,tabLentilles,tabCristaux,tabBombes};
}

nvs::Level * StarlightGame::getLevel(){
    return m_level;
}

