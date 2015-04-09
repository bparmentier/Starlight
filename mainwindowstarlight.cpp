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
    m_action_aide->setShortcut(QString("CTRL+A"));
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
    connect(ui->action_Quitter, &QAction::triggered,
            &QCoreApplication::quit);
    connect(ui->action_Nouveau, &QAction::triggered,
            this, &MainWindowStarlight::creerPartie);
    connect(ui->action_Fermer, &QAction::triggered,
            this, &MainWindowStarlight::fermerPartie);
    connect(m_action_aide, &QAction::triggered,
            this, &MainWindowStarlight::aide);
}

void MainWindowStarlight::creerPartie()
{
    if(m_jeu != nullptr){
        if(m_jeu->getLevel()->won() || m_jeu->getLevel()->lost()){
            fermerPartie();
        }else{
            QMessageBox::StandardButton reponse = QMessageBox::question(
                        this,
                        "Nouvelle partie",
                        "Êtes-vous sûr de vouloir commencer une nouvelle partie ?",
                        QMessageBox::Yes|QMessageBox::No);
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
        QMessageBox::information(this, "Erreur !", err.c_str());
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
    QString msg {
        "<p>Starlight est un petit jeu en deux dimensions se jouant sur une carte "
        "rectangulaire, comportant une source de lumière, émettant un rayon "
        "rectiligne. Le but du jeu est d'atteindre une cible avec ledit rayon, "
        "en évitant les obstacles via notamment des miroirs réléchissant la "
        "lumière.</p>"
        "<p>Les éléments du jeu sont les suivants : source, destination, "
        "mirroirs, murs, lentilles, cristaux et bombes.</p>"
        "<ul>"
        "<li>Seuls les miroirs peuvent être tournés&nbsp;;</li>"
        "<li>Les crystaux modifient la longueur d'onde du rayon&nbsp;;</li>"
        "<li>Les lentilles contrôlent le passage d'un rayon sur base de sa "
        "longueur d'onde&nbsp;;</li>"
        "<li>Dès que le rayon touche une bombe, la partie est perdue.</li>"
        "</ul>"
        "<p>Veillez à ce que le fichier .map ne soit pas erroné.</p></html>"};
    QMessageBox::information(this, "Aide", msg);
}

Ui::MainWindowStarlight * MainWindowStarlight::getUi() const{
    return ui;
}
