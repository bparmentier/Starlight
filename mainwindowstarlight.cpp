#include "mainwindowstarlight.h"
#include "ui_mainwindowstarlight.h"
#include "dialogconfig.h"
#include "observateurstarlight.h"
#include <QMessageBox>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

#include "levelchooserdialog.h"

MainWindowStarlight::MainWindowStarlight(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindowStarlight),
    m_level(nullptr), m_gameObs(nullptr)
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
    delete m_level;
    m_level = nullptr;
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
    connect(ui->action_Ouvrir, &QAction::triggered,
            this, &MainWindowStarlight::openFile);
    connect(ui->action_Fermer, &QAction::triggered,
            this, &MainWindowStarlight::closeGame);
    connect(m_action_aide, &QAction::triggered,
            this, &MainWindowStarlight::help);
}

void MainWindowStarlight::readMap(QString fileName)
{
    char element;
    int mapWidth, mapHeight, wavelength, mod, wlmin, wlmax;
    double x, y, x1, x2, y1, y2, width, height, length, edge, rad, alpha;

    std::vector<nvs::Crystal> crystals;
    std::vector<nvs::Wall> walls;
    std::vector<nvs::Lens> lenses;
    std::vector<nvs::Mirror> mirrors;
    std::vector<nvs::Bomb> bombs;
    nvs::SourceOfLight source;
    nvs::Target target;

    QFile mapFile(fileName);
    if (!mapFile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::runtime_error("Impossible d'ouvrir le fichier de carte");

    QTextStream in(&mapFile);

    /* first line: width and height */
    in >> mapWidth >> mapHeight;

    /* map components */
    while (!in.atEnd()) {
        in >> element;
        switch (element) {
        case 'S':
            in >> x >> y >> edge >> alpha >> wavelength;
            source = nvs::SourceOfLight{x, y, edge, alpha, wavelength};
            break;
        case 'D':
            in >> x >> y >> edge;
            target = nvs::Target{x, y, edge};
            break;
        case 'C':
            in >> x >> y >> rad >> mod;
            crystals.push_back(nvs::Crystal{x, y, rad, mod});
            break;
        case 'L':
            in >> x >> y >> width >> height >> wlmin >> wlmax;
            lenses.push_back(nvs::Lens{x, y, width, height, wlmax, wlmin});
            break;
        case 'W':
            in >> x1 >> y1 >> x2 >> y2;
            walls.push_back(nvs::Wall{x1, y1, x2, y2});
            break;
        case 'N':
            in >> x >> y >> rad;
            bombs.push_back(nvs::Bomb{x, y, rad});
            break;
        case 'M':
            in >> x >> y >> length >> alpha;
            mirrors.push_back(nvs::Mirror{x, y, length, alpha});
            break;
        }
    }
    mapFile.close();
    m_level = new nvs::Level{mapWidth, mapHeight, source, target,
            walls, mirrors, lenses, crystals, bombs};
}

void MainWindowStarlight::newGame()
{
    if (m_level != nullptr) {
        if (m_level->won() || m_level->lost()) {
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

    LevelChooserDialog lcd{this};
    auto lcdRetVal = lcd.exec();

    if (lcdRetVal == QDialog::Rejected) return;

    QString fileName(":level_");
    fileName.append(QString::number(lcd.getLevel()));
    try {
        readMap(fileName);
        setObserver();
    } catch(std::runtime_error err) {
        QMessageBox::information(this, "Erreur", err.what());
    }
}

void MainWindowStarlight::openFile()
{
    if (m_level != nullptr) {
        if (m_level->won() || m_level->lost()) {
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
        readMap(cd.getFileName());
        setObserver();
    } catch(std::runtime_error err) {
        QMessageBox::information(this, "Erreur", err.what());
    }
}

void MainWindowStarlight::setObserver()
{
    this->m_gameObs = new ObservateurStarlight(m_level, this);
    ui->graphicsView->setFixedSize(m_level->width() + 2,
                                   m_level->height() + 2);
    ui->graphicsView->setScene(m_gameObs);
    ui->graphicsView->show();
    ui->centralWidget->setEnabled(true);
}

void MainWindowStarlight::closeGame()
{
    delete m_gameObs;
    m_gameObs = nullptr;
    delete m_level;
    m_level = nullptr;
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
