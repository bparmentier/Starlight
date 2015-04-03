#include "mainwindowstarlight.h"
#include "ui_mainwindowstarlight.h"
#include "dialogconfig.h"
#include "observateurstarlight.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowStarlight)
{
    ui->setupUi(this);
    action_aide = ui->menuBar->addAction(tr("&Aide"));
    this->connexion();
    ui->centralWidget->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete obserJeu;
    obserJeu = nullptr;
    delete jeu;
    jeu = nullptr;
    delete ui;
    ui = nullptr;
}

void MainWindow::connexion(){
    ui->action_Nouveau->setShortcut(QString("CTRL+N"));
    ui->action_Fermer->setShortcut(QString("CTRL+F"));
    ui->action_Quitter->setShortcut(QString("CTRL+Q"));
    action_aide->setShortcut(QString("CTRL+A"));
    connect(ui->action_Quitter, &QAction::triggered,&QCoreApplication::quit);
    connect(ui->action_Nouveau, &QAction::triggered, this, &MainWindow::creerPartie);
    connect(ui->action_Fermer, &QAction::triggered, this, &MainWindow::fermerPartie);
    connect(action_aide, &QAction::triggered, this, &MainWindow::aide);
}

void MainWindow::creerPartie(){
    if(jeu != nullptr){
        QMessageBox::StandardButton reponse = QMessageBox::question(this, "new game", "Êtes-vous sûr de vouloir commencer une nouvelle partie?",
                                                                    QMessageBox::Yes|QMessageBox::No);
        if (reponse == QMessageBox::Yes) {
            fermerPartie();
        } else {
            return;
        }
    }
    DialogConfig cd {this};
    auto retour = cd.exec();

    if (retour == QDialog::Rejected) return;
    try{
        jeu = new StarlightGame(cd.getNomFichier().toStdString());
        this->obserJeu = new ObservateurStarlight(jeu->getLevel());
        ui->graphicsView->setFixedSize(jeu->getLevel()->width()+5,jeu->getLevel()->height()+5);
        ui->graphicsView->setScene(obserJeu);
        ui->graphicsView->show();
        ui->centralWidget->setEnabled(true);
    }catch(std::string err){
        QMessageBox::information(this,"Error !", err.c_str());
    }
}

void MainWindow::fermerPartie(){
    delete obserJeu;
    obserJeu = nullptr;
    delete jeu;
    jeu = nullptr;
    ui->graphicsView->hide();
    ui->centralWidget->setDisabled(true);
}

void MainWindow::aide(){
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
