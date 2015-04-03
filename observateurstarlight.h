#ifndef OBSERVATEURSTARLIGHT_H
#define OBSERVATEURSTARLIGHT_H

#include "o_sdo/observateur.h"
#include "starlightgame.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QtGui>
#include <QGraphicsItem>

class ObservateurStarlight : public QGraphicsScene, public Observateur
{
    nvs::Level * m_niveau = nullptr;

public:
    ObservateurStarlight(nvs::Level * niveau, QWidget * parent = 0);
    ~ObservateurStarlight();
    void rafraichir(SujetDObservation * sdo);
    void dessinerSourceAndDestination();
    void dessinerMurs();
    void dessinerLentilles();
    void dessinerCristaux();
    void dessinerBombes();
    void dessinerMiroirs();
};

#endif // OBSERVATEURSTARLIGHT_H
