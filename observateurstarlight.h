#ifndef OBSERVATEURSTARLIGHT_H
#define OBSERVATEURSTARLIGHT_H

#include "o_sdo/observateur.h"
#include "starlight/level.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QtGui>
#include <QGraphicsItem>
#include <QSound>

/*!
 * \brief The ObservateurStarlight class
 */
class ObservateurStarlight : public QGraphicsScene, public Observateur
{
    nvs::Level *m_level;
    QGraphicsRectItem *m_source;
    QGraphicsRectItem *m_target;
    std::vector<std::pair<QGraphicsLineItem *, nvs::Mirror *>> m_mirrors;
    std::vector<std::pair<QGraphicsEllipseItem *, const nvs::Bomb *>> m_bombs;
    std::vector<QGraphicsLineItem *> m_lightRays;
    QSound laserSound;

public:

    /*!
     * \brief Construuit un ObservateurStarlight avec le *level* et le *parent*
     * donné en paramètres.
     * \param level le niveau du jeu
     * \param parent
     */
    ObservateurStarlight(nvs::Level *level, QWidget *parent = 0);

    ~ObservateurStarlight();

    /*!
     * \brief rafraichir
     * \param sdo
     */
    void rafraichir(SujetDObservation *sdo);

private:

    /*!
     * \brief Dessine la source du rayon et la cible à atteindre
     */
    void drawSourceAndTarget();

    /*!
     * \brief Dessine les murs
     */
    void drawWalls();

    /*!
     * \brief Dessine les lentilles
     */
    void drawLenses();

    /*!
     * \brief Dessine les cristaux
     */
    void drawCrystals();

    /*!
     * \brief Dessine les bombes
     */
    void drawBombs();

    /*!
     * \brief Dessines les mirroirs
     */
    void drawMirrors();

    /*!
     * \brief Dessine les rayons lumineux
     */
    void drawLightRays();

    /*!
     * \brief Supprime les rayons lumineux
     */
    void removeLightRays();

    /*!
     * \brief Retourne l'indice de l'*element* dans la liste des mirroirs
     * \param element l'élément à trouver
     * \return l'indice de l'*element* dans la liste des mirroirs
     */
    int findElement(QGraphicsLineItem *element);

    /*!
     * \brief Affiche un message d'information lorsque le jeu est terminé
     */
    void gameInfo();

    /*!
     * \brief Active ou désactive la source du rayon lumineux
     * \param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /*!
     * \brief Réalise une rotation horlogique ou anti-horlogique de l'élément
     * sélectionné en fonction de la touche pressée
     * \param event
     */
    void keyPressEvent(QKeyEvent *event);
};

#endif // OBSERVATEURSTARLIGHT_H
