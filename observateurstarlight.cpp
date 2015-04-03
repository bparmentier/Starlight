#include "observateurstarlight.h"
#include <iostream>

ObservateurStarlight::ObservateurStarlight(nvs::Level * niveau, QWidget * parent):
    QGraphicsScene{parent}, m_niveau{niveau}
{
    m_niveau->attacher(this);
    this->setSceneRect(0,0,m_niveau->width(),m_niveau->height());
    rafraichir(m_niveau);
}

ObservateurStarlight::~ObservateurStarlight()
{
    m_niveau->detacher(this);
}

void ObservateurStarlight::rafraichir(SujetDObservation * sdo){
    if(sdo!=m_niveau){
        return;
    }
    dessinerSourceAndDestination();
    dessinerMurs();
    dessinerLentilles();
    dessinerCristaux();
    dessinerBombes();
    dessinerMiroirs();
}

void ObservateurStarlight::dessinerSourceAndDestination(){
    nvs::Point2Dd point = m_niveau->source().shape().topLeft();
    int edge = m_niveau->source().shape().width();
    this->addRect(point.x(),point.y(),edge,edge);
    point = m_niveau->target().shape().topLeft();
    edge = m_niveau->target().shape().width();
    this->addRect(point.x(),point.y(),edge,edge);
}

void ObservateurStarlight::dessinerMurs(){
    QPen penMirrors{QBrush{Qt::black},2};
    nvs::Segment line;
    for(int i = 0; i<m_niveau->walls().size(); i++){
        line = m_niveau->walls().at(i).shape();
        this->addLine(line.first().x(),line.first().y(),line.second().x(),line.second().y(),penMirrors);
    }
}

void ObservateurStarlight::dessinerLentilles(){
    for(int i = 0; i<m_niveau->lenses().size(); i++){
        nvs::Point2Dd point = m_niveau->lenses().at(i).shape().topLeft();
        int largeur = m_niveau->lenses().at(i).shape().width();
        int longueur = m_niveau->lenses().at(i).shape().height();
        this->addRect(point.x(),point.y(),largeur,longueur);
    }
}

void ObservateurStarlight::dessinerCristaux(){
    for(int i = 0; i<m_niveau->crystals().size(); i++){
        nvs::Point2Dd point = m_niveau->crystals().at(i).shape().center();
        double rayon = m_niveau->crystals().at(i).shape().radius();
        this->addEllipse(point.x(),point.y(),rayon,rayon,QPen(Qt::black));
    }
}

void ObservateurStarlight::dessinerBombes(){
    for(int i = 0; i<m_niveau->bombs().size(); i++){
        nvs::Point2Dd point = m_niveau->bombs().at(i).shape().center();
        double rayon = m_niveau->bombs().at(i).shape().radius();
        this->addEllipse(point.x(),point.y(),rayon,rayon,QPen(Qt::black),QBrush(QColor(Qt::red)));
    }
}

void ObservateurStarlight::dessinerMiroirs(){
    QPen penMirrors{QBrush{Qt::black},5};
    nvs::Segment line;
    for(int i = 0; i<m_niveau->mirrors().size(); i++){
        line = m_niveau->mirrors().at(i).shape();
        this->addLine(line.first().x(),line.first().y(),line.second().x(),line.second().y(),penMirrors);
    }
}
