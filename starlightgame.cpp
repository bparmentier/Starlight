#include "starlightgame.h"
#include <iostream>
#include <fstream>

using namespace std;

StarlightGame::StarlightGame(const string &fileName)
{
    readMap(fileName);
}

StarlightGame::~StarlightGame()
{
    delete m_level;
    m_level = nullptr;
}

void StarlightGame::readMap(const string &fileName)
{
    ifstream file{fileName};
    char element;
    int mapWidth, mapHeight, wavelength, mod, wlmin, wlmax;
    double x, y, x1, x2, y1, y2, width, height, length, edge, rad, alpha;

    vector<nvs::Crystal> crystals;
    vector<nvs::Wall> walls;
    vector<nvs::Lens> lenses;
    vector<nvs::Mirror> mirrors;
    vector<nvs::Bomb> bombs;
    nvs::SourceOfLight source;
    nvs::Target target;

    if (!file.is_open()) {
        string msg { "Fichier : \"" };
        msg += fileName;
        msg += "\" introuvable.";
        throw msg;
    }

    /* first line: width and height */
    file >> mapWidth >> mapHeight;

    /* map components */
    while (file >> element) {
        switch (element) {
        case 'S':
            file >> x >> y >> edge >> alpha >> wavelength;
            source = nvs::SourceOfLight{x, y, edge, alpha, wavelength};
            break;
        case 'D':
            file >> x >> y >> edge;
            target = nvs::Target{x, y, edge};
            break;
        case 'C':
            file >> x >> y >> rad >> mod;
            crystals.push_back(nvs::Crystal{x, y, rad, mod});
            break;
        case 'L':
            file >> x >> y >> width >> height >> wlmin >> wlmax;
            lenses.push_back(nvs::Lens{x, y, width, height, wlmax, wlmin});
            break;
        case 'W':
            file >> x1 >> y1 >> x2 >> y2;
            walls.push_back(nvs::Wall{x1, y1, x2, y2});
            break;
        case 'N':
            file >> x >> y >> rad;
            bombs.push_back(nvs::Bomb{x, y, rad});
            break;
        case 'M':
            file >> x >> y >> length >> alpha;
            mirrors.push_back(nvs::Mirror{x, y, length, alpha});
            break;
        }
    }
    m_level = new nvs::Level{mapWidth, mapHeight, source, target,
            walls, mirrors, lenses, crystals, bombs};
}

nvs::Level * StarlightGame::getLevel(){
    return m_level;
}

