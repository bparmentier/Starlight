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
    this->connection();
    ui->centralWidget->setDisabled(true);
}

MainWindowStarlight::~MainWindowStarlight()
{
    delete m_gameObs;
    m_gameObs = nullptr;
    delete m_game;
    m_game = nullptr;
    delete m_action_aide;
    m_action_aide = nullptr;
    delete ui;
    ui = nullptr;
}

void MainWindowStarlight::connection()
{
    connect(ui->action_Quitter, &QAction::triggered,
            &QCoreApplication::quit);
    connect(ui->action_Nouveau, &QAction::triggered,
            this, &MainWindowStarlight::newGame);
    connect(ui->action_Fermer, &QAction::triggered,
            this, &MainWindowStarlight::closeGame);
    connect(m_action_aide, &QAction::triggered,
            this, &MainWindowStarlight::help);
}

void MainWindowStarlight::newGame()
{
    if (m_game != nullptr) {
        if (m_game->getLevel()->won() || m_game->getLevel()->lost()) {
            closeGame();
        } else {
            QMessageBox::StandardButton newGameRetVal = QMessageBox::question(
                        this,
                        "Nouvelle partie",
                        "Êtes-vous sûr de vouloir commencer une nouvelle partie ?",
                        QMessageBox::Yes | QMessageBox::No);
            if (newGameRetVal == QMessageBox::Yes) {
                closeGame();
            } else {
                return;
            }
        }
    }

    DialogConfig cd{this};
    auto cdRetVal = cd.exec();

    if (cdRetVal == QDialog::Rejected) return;
    try {
        m_game = new StarlightGame(cd.getFileName().toStdString());
        this->m_gameObs = new ObservateurStarlight(m_game->getLevel(), this);
        ui->graphicsView->setFixedSize(m_game->getLevel()->width() + 2,
                                       m_game->getLevel()->height() + 2);
        ui->graphicsView->setScene(m_gameObs);
        ui->graphicsView->show();
        ui->centralWidget->setEnabled(true);
    } catch(std::string err) {
        QMessageBox::information(this, "Erreur !", err.c_str());
    }
}

void MainWindowStarlight::closeGame()
{
    delete m_gameObs;
    m_gameObs = nullptr;
    delete m_game;
    m_game = nullptr;
    ui->graphicsView->hide();
    ui->centralWidget->setDisabled(true);
}

void MainWindowStarlight::help()
{
    QString msg{
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
