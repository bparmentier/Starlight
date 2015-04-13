#include "observateurstarlight.h"
#include <iostream>
#include <typeinfo>
#include <QMessageBox>
#include "mainwindowstarlight.h"

ObservateurStarlight::ObservateurStarlight(nvs::Level *level, QWidget *parent) :
    QGraphicsScene{parent}, m_level{level}
{
    m_level->attacher(this);
    this->setSceneRect(0, 0, m_level->width(), m_level->height());
    drawSourceAndTarget();
    drawWalls();
    drawLenses();
    drawCrystals();
    drawBombs();
    drawMirrors();
}

ObservateurStarlight::~ObservateurStarlight()
{
    for (int i = 0; i < m_lightRays.size(); i++) {
        delete m_lightRays.at(i);
        m_lightRays.at(i) = nullptr;
    }
    m_lightRays.clear();

    for (int i = 0; i < m_mirrors.size(); i++) {
        delete m_mirrors.at(i).first;
        m_mirrors.at(i).first = nullptr;
    }
    m_mirrors.clear();

    delete m_target;
    m_target = nullptr;

    delete m_source;
    m_source = nullptr;

    m_level->detacher(this);
}

void ObservateurStarlight::rafraichir(SujetDObservation *sdo)
{
    if (sdo != m_level) {
        return;
    }
    drawLightRays();
}

void ObservateurStarlight::drawSourceAndTarget()
{
    nvs::Point2Dd point = m_level->source().shape().topLeft();
    int edgeLength = m_level->source().shape().width();
    m_source = this->addRect(point.x(), point.y(), edgeLength, edgeLength,
                             QPen(QBrush(Qt::black), 1), QBrush(Qt::darkGreen));
    m_source->setCursor(QCursor(Qt::PointingHandCursor));
    point = m_level->target().shape().topLeft();
    edgeLength = m_level->target().shape().width();
    m_target = this->addRect(point.x(), point.y(), edgeLength, edgeLength,
                                  QPen(QBrush(Qt::black), 1), QBrush(Qt::black));
}

void ObservateurStarlight::drawWalls()
{
    QPen wallStyle{QBrush{Qt::black}, 2};
    nvs::Segment line;
    for (int i = 0; i < m_level->walls().size(); i++) {
        line = m_level->walls().at(i).shape();
        this->addLine(line.first().x(), line.first().y(),
                      line.second().x(), line.second().y(),
                      wallStyle);
    }
}

void ObservateurStarlight::drawLenses()
{
    for (int i = 0; i < m_level->lenses().size(); i++) {
        nvs::Point2Dd point = m_level->lenses().at(i).shape().topLeft();
        int width = m_level->lenses().at(i).shape().width();
        int height = m_level->lenses().at(i).shape().height();
        this->addRect(point.x(), point.y(), width, height);
    }
}

void ObservateurStarlight::drawCrystals()
{
    for (int i = 0; i < m_level->crystals().size(); i++) {
        nvs::Point2Dd point = m_level->crystals().at(i).shape().center();
        double radius = m_level->crystals().at(i).shape().radius();
        this->addEllipse(point.x() - radius, point.y() - radius,
                         radius * 2, radius * 2, QPen(Qt::black));
    }
}

void ObservateurStarlight::drawBombs()
{
    for (int i = 0; i < m_level->bombs().size(); i++) {
        nvs::Point2Dd point = m_level->bombs().at(i).shape().center();
        double radius = m_level->bombs().at(i).shape().radius();
        std::pair<QGraphicsEllipseItem *, const nvs::Bomb *> bomb{
            this->addEllipse(
                    point.x() - radius, point.y() - radius,
                    radius * 2, radius * 2, QPen(Qt::black),
                    QBrush(QColor(Qt::black))),
            &m_level->bombs().at(i)
        };
        m_bombs.push_back(bomb);
    }
}

void ObservateurStarlight::drawMirrors()
{
    QPen mirrorStyle{QBrush{Qt::darkBlue}, 5};
    nvs::Segment line;
    for (int i = 0; i < m_level->mirrors().size(); i++) {
        line = m_level->mirrors().at(i).shape();
        std::pair<QGraphicsLineItem *, nvs::Mirror *> mirror{
            this->addLine(line.first().x(), line.first().y(),
                          line.second().x(), line.second().y(),
                          mirrorStyle),
            &m_level->mirrors().at(i)
        };
        mirror.first->setFlag(QGraphicsLineItem::ItemIsSelectable);
        mirror.first->setCursor(QCursor(Qt::PointingHandCursor));
        mirror.first->setTransformOriginPoint(
                    ((line.first().x() + line.second().x()) / 2),
                    ((line.first().y() + line.second().y()) / 2));
        m_mirrors.push_back(mirror);
    }
}

void ObservateurStarlight::drawLightRays()
{
    QPen lightRayStyle{QBrush{Qt::red}, 1};
    nvs::Segment line;
    for (int i = 0; i < m_level->boundedRays().size(); i++) {
        line = m_level->boundedRays().at(i).first;
        m_lightRays.push_back(
                    this->addLine(line.first().x(), line.first().y(),
                                  line.second().x(), line.second().y(),
                                  lightRayStyle));
    }
}

void ObservateurStarlight::removeLightRays()
{
    for (int i = 0; i < m_lightRays.size(); i++) {
        this->removeItem(m_lightRays.at(i));
        delete m_lightRays.at(i);
        m_lightRays.at(i) = nullptr;
    }
    m_lightRays.clear();
}

int ObservateurStarlight::findElement(QGraphicsLineItem *element)
{
    bool found = false;
    int i = 0;
    while (i < m_mirrors.size() && !found) {
        if (element == m_mirrors.at(i).first) {
            found = true;
        } else {
            i++;
        }
    }
    return i;
}

void ObservateurStarlight::gameInfo(){
    if (m_level->won() || m_level->lost()) {
        QString msg;
        if (m_level->won()) {
            m_target->setBrush(QBrush(Qt::green));
            msg = "Vous avez gagné, bravo !";
        }
        if (m_level->lost()) {
            for (int i = 0; i < m_bombs.size(); i++) {
                if (m_bombs.at(i).second->enlightened())
                    m_bombs.at(i).first->setBrush(QBrush(QColor(Qt::red)));
            }
            msg = "Vous avez perdu, veuillez recommencer !";
        }
        QMessageBox::information((QWidget *) this->parent(),
                                 "Fin de partie", msg);
        ((MainWindowStarlight *) this->parent())->centralWidget()->setDisabled(true);
    }
}

void ObservateurStarlight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    QGraphicsItem *element = this->itemAt(event->lastScenePos().x(),
                                           event->lastScenePos().y(),
                                           QTransform());
    if (m_source == element) {
        if (m_level->source().isOn()) {
            m_level->source().switchOff();
            m_source->setBrush(QBrush(Qt::darkGreen));
            removeLightRays();
        } else {
            m_level->source().switchOn();
            m_source->setBrush(QBrush(Qt::green));
            drawLightRays();
            gameInfo();
        }
    }
}

void ObservateurStarlight::keyPressEvent(QKeyEvent *event)
{
    if (!this->selectedItems().isEmpty() && this->selectedItems().size() == 1) {
        QGraphicsLineItem *mirror = (QGraphicsLineItem *) this->selectedItems().first();
        nvs::Mirror *element = m_mirrors.at(findElement(mirror)).second;
        if (event->key() == Qt::Key_Up) {
            mirror->setRotation(mirror->rotation() - 1);
            element->rotate(+((1 * M_PI) / 180));
        }
        if (event->key() == Qt::Key_Down) {
            mirror->setRotation(mirror->rotation() + 1);
            element->rotate(-((1 * M_PI) / 180));
        }
        removeLightRays();
        rafraichir(m_level);
        gameInfo();
    }
}
