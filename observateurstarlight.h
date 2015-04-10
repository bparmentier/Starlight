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
    nvs::Level *m_level = nullptr;
    QGraphicsRectItem *m_source = nullptr;
    QGraphicsRectItem *m_target = nullptr;
    std::vector<std::pair<QGraphicsLineItem *, nvs::Mirror *>> m_mirrors;
    std::vector<QGraphicsLineItem *> m_lightRays;

public:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    ObservateurStarlight(nvs::Level *level, QWidget *parent = 0);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    ~ObservateurStarlight();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void rafraichir(SujetDObservation *sdo);

private:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawSourceAndTarget();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawWalls();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawLenses();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawCrystals();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawBombs();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawMirrors();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void drawLightRays();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void removeLightRays();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    int findElement(QGraphicsLineItem *element);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void gameInfo();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void keyPressEvent(QKeyEvent *event);
};

#endif // OBSERVATEURSTARLIGHT_H
