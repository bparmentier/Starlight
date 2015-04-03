#include "starlightgame.h"
#include <iostream>
#include <fstream>

using namespace std;

StarlightGame::StarlightGame(const string & fileName)
{
    readMap(fileName);
}

StarlightGame::~StarlightGame()
{
    delete m_level;
    m_level = nullptr;
}

void StarlightGame::readMap(const string & fileName){
    ifstream file{fileName};
    char component;
    int x, y, width, height, widthMap, heightMap, length, edge,
            wavelength, rad, mod, wlmin, wlmax, x1, y1, x2, y2;
    double alpha;

    vector<nvs::Crystal> tabCrystal;
    vector<nvs::Wall> tabWalls;
    vector<nvs::Lens> tabLens;
    vector<nvs::Mirror> tabMirrors;
    vector<nvs::Bomb> tabBombs;
    nvs::SourceOfLight source;
    nvs::Target destination;

    if (!file.is_open()) {
        string msg { "Fichier : \"" };
        msg += fileName;
        msg += "\" introuvable.";
        throw msg;
    }

    /* first line: width and height */
    file >> widthMap >> heightMap;

    /* map components */
    while (file >> component) {
        switch (component) {
        case 'S':
            file >> x >> y >> edge >> alpha >> wavelength;
            source = nvs::SourceOfLight {x,y,edge,alpha,wavelength};
            break;
        case 'D':
            file >> x >> y >> edge;
            destination = nvs::Target {x,y,edge};
            break;
        case 'C':
            file >> x >> y >> rad >> mod;
            tabCrystal.push_back(nvs::Crystal{x,y,rad,mod});
            break;
        case 'L':
            file >> x >> y >> width >> height >> wlmin >> wlmax;
            tabLens.push_back(nvs::Lens{x,y,width,height,wlmax,wlmin});
            break;
        case 'W':
            file >> x1 >> y1 >> x2 >> y2;
            tabWalls.push_back(nvs::Wall{x1,y1,x2,y2});
            break;
        case 'N':
            file >> x >> y >> rad;
            tabBombs.push_back(nvs::Bomb{x,y,rad});
            break;
        case 'M':
            file >> x >> y >> length >> alpha;
            tabMirrors.push_back(nvs::Mirror{x,y,length,alpha});
            break;
        }
    }
    m_level = new nvs::Level{widthMap,heightMap,source,destination,
            tabWalls,tabMirrors,tabLens,tabCrystal,tabBombs};
}

nvs::Level * StarlightGame::getLevel(){
    return m_level;
}

