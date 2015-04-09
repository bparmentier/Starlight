#include "mainwindowstarlight.h"
#include "ui_mainwindowstarlight.h"
#include "dialogconfig.h"
#include "observateurstarlight.h"
#include <QMessageBox>

MainWindowStarlight::MainWindowStarlight(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindowStarlight)
{
    ui->setupUi(this);
    m_action_aide = ui->menuBar->addAction(tr("&Aide"));
    this->connexion();
    ui->centralWidget->setDisabled(true);
}

MainWindowStarlight::~MainWindowStarlight()
{
    delete m_obserJeu;
    m_obserJeu = nullptr;
    delete m_jeu;
    m_jeu = nullptr;
    delete m_action_aide;
    m_action_aide = nullptr;
    delete ui;
    ui = nullptr;
}

void MainWindowStarlight::connexion()
{
    ui->action_Nouveau->setShortcut(QString("CTRL+N"));
    ui->action_Fermer->setShortcut(QString("CTRL+F"));
    ui->action_Quitter->setShortcut(QString("CTRL+Q"));
    m_action_aide->setShortcut(QString("CTRL+A"));
    connect(ui->action_Quitter, &QAction::triggered,this,&QCoreApplication::quit);
    connect(ui->action_Nouveau, SIGNAL(triggered()), this, SLOT(creerPartie()));
    connect(ui->action_Fermer, SIGNAL(triggered()), this, SLOT(fermerPartie()));
    connect(m_action_aide, SIGNAL(triggered()), this, SLOT(aide()));
}

void MainWindowStarlight::creerPartie()
{
    if(m_jeu != nullptr){
        if(m_jeu->getLevel()->won() || m_jeu->getLevel()->lost()){
            fermerPartie();
        }else{
            QMessageBox::StandardButton reponse = QMessageBox::question(this, "new game",
                "Êtes-vous sûr de vouloir commencer une nouvelle partie?", QMessageBox::Yes|QMessageBox::No);
            if (reponse == QMessageBox::Yes) {
                fermerPartie();
            } else {
                return;
            }
        }
    }

    DialogConfig cd {this};
    auto retour = cd.exec();

    if (retour == QDialog::Rejected) return;
    try{
        m_jeu = new StarlightGame(cd.getNomFichier().toStdString());
        this->m_obserJeu = new ObservateurStarlight(m_jeu->getLevel(),this);
        ui->graphicsView->setFixedSize(m_jeu->getLevel()->width()+2,m_jeu->getLevel()->height()+2);
        ui->graphicsView->setScene(m_obserJeu);
        ui->graphicsView->show();
        ui->centralWidget->setEnabled(true);
    }catch(std::string err){
        QMessageBox::information(this,"Error !", err.c_str());
    }
}

void MainWindowStarlight::fermerPartie()
{
    delete m_obserJeu;
    m_obserJeu = nullptr;
    delete m_jeu;
    m_jeu = nullptr;
    ui->graphicsView->hide();
    ui->centralWidget->setDisabled(true);
}

void MainWindowStarlight::aide()
{
    QString msg {"<html><center><p><b>Aide starlight</b></p></center>"
                 "<p>Starlight est un jeu de refelxion de lumière dont le but est de d'amener \n"
                 "un rayon d'une source de départ à une source de destination.</p>"
                 "<p>Information sur le jeu :</p>"
                 "<ul><li>Éléments du jeu : source, destination, mirroir, mur, lentille, cristale et bombe.</li>"
                 "<li>Seul les miroirs peuvent etre tourner.</li>"
                 "<li>Les crystaux modifient la longueur d'onde du rayon.</li>"
                 "<li>Les lentilles controle le passage d'un rayon sur base de sa longueur d'onde.</li>"
                 "<li>Les bombes font perdre la partie dés que le rayon en touche.</li></ul></br>"
                 "<p>Veillez à ce que le fichier .map ne soit pas erronées.</p></html>"};
    QMessageBox::information(this, "Aide", msg);
}

Ui::MainWindowStarlight * MainWindowStarlight::getUi() const{
    return ui;
}
