#include "observateurstarlight.h"
#include <iostream>
#include <typeinfo>
#include <QMessageBox>
#include "mainwindowstarlight.h"

ObservateurStarlight::ObservateurStarlight(nvs::Level * niveau, QWidget * parent):
    QGraphicsScene{parent}, m_niveau{niveau}
{
    m_niveau->attacher(this);
    this->setSceneRect(0,0,m_niveau->width(),m_niveau->height());
    dessinerSourceEtDestination();
    dessinerMurs();
    dessinerLentilles();
    dessinerCristaux();
    dessinerBombes();
    dessinerMiroires();
}

ObservateurStarlight::~ObservateurStarlight()
{
    for(int i = 0; i<m_tabRayons.size();i++){
        delete m_tabRayons.at(i);
        m_tabRayons.at(i) = nullptr;
    }
    m_tabRayons.clear();

    for(int i = 0; i<m_tabMiroires.size();i++){
        delete m_tabMiroires.at(i).first;
        m_tabMiroires.at(i).first = nullptr;
    }
    m_tabMiroires.clear();

    delete m_destination;
    m_destination = nullptr;

    delete m_source;
    m_source = nullptr;

    m_niveau->detacher(this);
}

void ObservateurStarlight::rafraichir(SujetDObservation * sdo)
{
    if(sdo!=m_niveau){
        return;
    }
    dessinerRayons();
}

void ObservateurStarlight::dessinerSourceEtDestination()
{
    nvs::Point2Dd point = m_niveau->source().shape().topLeft();
    int bord = m_niveau->source().shape().width();
    m_source = this->addRect(point.x(),point.y(),bord,bord,QPen(QBrush(Qt::black),1),QBrush(Qt::darkGreen));
    point = m_niveau->target().shape().topLeft();
    bord = m_niveau->target().shape().width();
    m_destination = this->addRect(point.x(), point.y(), bord, bord, QPen(QBrush(Qt::black),1), QBrush(Qt::black));
}

void ObservateurStarlight::dessinerMurs()
{
    QPen styloMur{QBrush{Qt::black},2};
    nvs::Segment ligne;
    for(int i = 0; i<m_niveau->walls().size(); i++){
        ligne = m_niveau->walls().at(i).shape();
        this->addLine(ligne.first().x(),ligne.first().y(),ligne.second().x(),ligne.second().y(),styloMur);
    }
}

void ObservateurStarlight::dessinerLentilles()
{
    for(int i = 0; i<m_niveau->lenses().size(); i++){
        nvs::Point2Dd point = m_niveau->lenses().at(i).shape().topLeft();
        int largeur = m_niveau->lenses().at(i).shape().width();
        int hauteur = m_niveau->lenses().at(i).shape().height();
        this->addRect(point.x(),point.y(),largeur,hauteur);
    }
}

void ObservateurStarlight::dessinerCristaux()
{
    for(int i = 0; i<m_niveau->crystals().size(); i++){
        nvs::Point2Dd point = m_niveau->crystals().at(i).shape().center();
        double rayon = m_niveau->crystals().at(i).shape().radius();
        this->addEllipse(point.x()-rayon, point.y()-rayon, rayon*2, rayon*2, QPen(Qt::black));
    }
}

void ObservateurStarlight::dessinerBombes()
{
    for(int i = 0; i<m_niveau->bombs().size(); i++){
        nvs::Point2Dd point = m_niveau->bombs().at(i).shape().center();
        double rayon = m_niveau->bombs().at(i).shape().radius();
        this->addEllipse(point.x()-rayon, point.y()-rayon, rayon*2, rayon*2, QPen(Qt::black), QBrush(QColor(Qt::red)));
    }
}

void ObservateurStarlight::dessinerMiroires()
{
    QPen styloMiroires{QBrush{Qt::darkBlue},5};
    nvs::Segment ligne;
    for(int i = 0; i<m_niveau->mirrors().size(); i++){
        m_niveau->mirrors().at(i);
        ligne = m_niveau->mirrors().at(i).shape();
        std::pair<QGraphicsLineItem*,nvs::Mirror *> mirroir
            {this->addLine(ligne.first().x(),ligne.first().y(),ligne.second().x(),ligne.second().y(),styloMiroires),&m_niveau->mirrors().at(i)};
        mirroir.first->setFlag(QGraphicsLineItem::ItemIsSelectable);
        mirroir.first->setTransformOriginPoint(((ligne.first().x() + ligne.second().x())/2),((ligne.first().y() + ligne.second().y())/2));
        m_tabMiroires.push_back(mirroir);
    }
}

void ObservateurStarlight::dessinerRayons()
{
    QPen styloRayons{QBrush{Qt::red},1};
    nvs::Segment ligne;
    for(int i = 0; i<m_niveau->boundedRays().size(); i++){
        ligne = m_niveau->boundedRays().at(i).first;
        m_tabRayons.push_back(this->addLine(ligne.first().x(),ligne.first().y(),ligne.second().x(),ligne.second().y(),styloRayons));
    }
}

void ObservateurStarlight::supprimerRayons()
{
    for(int i = 0; i<m_tabRayons.size();i++){
        this->removeItem(m_tabRayons.at(i));
        delete m_tabRayons.at(i);
        m_tabRayons.at(i) = nullptr;
    }
    m_tabRayons.clear();
}

int ObservateurStarlight::chercherElement(QGraphicsLineItem * element)
{
    bool trouve = false;
    int i = 0;
    while(i < m_tabMiroires.size() && !trouve){
        if(element == m_tabMiroires.at(i).first){
            trouve = true;
        }else{
            i++;
        }
    }
    return i;
}

void ObservateurStarlight::informationJeu(){
    if(m_niveau->won() || m_niveau->lost()){
        QString msg;
        if(m_niveau->won()){
            m_destination->setBrush(QBrush(Qt::green));
            msg = QString{"<html><center><p><b>Vous avez gagnez, Bravo !</b></p></center></html>"};
        }
        if(m_niveau->lost()){
            msg = QString{"<html><center><p><b>Vous avez perdu, veuillez recommencer !</b></p></center></html>"};
        }
        QMessageBox::information((QWidget*)this->parent(),"Information Partie", msg);
        ((MainWindowStarlight*)this->parent())->centralWidget()->setDisabled(true);
    }
}

void ObservateurStarlight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem * element = this->itemAt(event->lastScenePos().x(), event->lastScenePos().y(),QTransform());
    if(m_source == element){
        if(m_niveau->source().isOn()){
            m_niveau->source().switchOff();
            m_source->setBrush(QBrush(Qt::darkGreen));
            supprimerRayons();
        }else{
            m_niveau->source().switchOn();
            m_source->setBrush(QBrush(Qt::green));
            dessinerRayons();
            informationJeu();
        }
    }
}

void ObservateurStarlight::keyPressEvent(QKeyEvent *event)
{
    if(!this->selectedItems().isEmpty() && this->selectedItems().size() == 1){
        QGraphicsLineItem * miroir = (QGraphicsLineItem *)this->selectedItems().first();
        nvs::Mirror * element = m_tabMiroires.at(chercherElement(miroir)).second;
        if(event->key() == Qt::Key_Up){
            miroir->setRotation(miroir->rotation()-1);
            element->rotate(+((1*M_PI)/180));
        }
        if(event->key() == Qt::Key_Down){
            miroir->setRotation(miroir->rotation()+1);
            element->rotate(-((1*M_PI)/180));
        }
        supprimerRayons();
        rafraichir(m_niveau);
        informationJeu();
    }
}
