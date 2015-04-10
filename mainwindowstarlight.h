#ifndef MAINWINDOWSTARLIGHT_H
#define MAINWINDOWSTARLIGHT_H

#include <QMainWindow>
#include "starlightgame.h"
#include "observateurstarlight.h"

namespace Ui {
class MainWindowStarlight;
}

class MainWindowStarlight : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindowStarlight *ui = nullptr;
    QAction *m_action_aide = nullptr;
    StarlightGame *m_game = nullptr;
    ObservateurStarlight *m_gameObs = nullptr;


public:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    explicit MainWindowStarlight(QWidget *parent = 0);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    ~MainWindowStarlight();
    Ui::MainWindowStarlight * getUi() const;

private:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void connection();

private slots:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void newGame();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void closeGame();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void help();
};

#endif // MAINWINDOWSTARLIGHT_H
