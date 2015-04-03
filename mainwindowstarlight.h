#ifndef MAINWINDOWSTARLIGHT_H
#define MAINWINDOWSTARLIGHT_H

#include <QMainWindow>
#include "starlightgame.h"
#include "observateurstarlight.h"

namespace Ui {
class MainWindowStarlight;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindowStarlight *ui;
    QAction *action_aide = nullptr;
    StarlightGame *jeu = nullptr;
    ObservateurStarlight *obserJeu = nullptr;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void connexion();

private slots:
    void creerPartie();
    void fermerPartie();
    void aide();
};

#endif // MAINWINDOWSTARLIGHT_H
