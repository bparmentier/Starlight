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
    void dessinerSourceEtDestination();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void dessinerMurs();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void dessinerLentilles();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void dessinerCristaux();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void dessinerBombes();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void dessinerMiroires();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void dessinerRayons();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void supprimerRayons();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    int chercherElement(QGraphicsLineItem *element);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void informationJeu();

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
