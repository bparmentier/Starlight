#ifndef MAINWINDOWSTARLIGHT_H
#define MAINWINDOWSTARLIGHT_H

#include <QMainWindow>
#include "starlightgame.h"
#include "observateurstarlight.h"

namespace Ui {
class MainWindowStarlight;
}

/*!
 * \brief The MainWindowStarlight class
 */
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
     * \brief Construit une MainWindowStarlight avec le *parent* donné en
     * paramètre.
     * \param parent
     */
    explicit MainWindowStarlight(QWidget *parent = 0);

    ~MainWindowStarlight();

    /*!
     * \brief getUi
     * \return
     */
    Ui::MainWindowStarlight * getUi() const;

private:

    /*!
     * \brief connection
     */
    void connection();

private slots:

    /*!
     * \brief newGame
     */
    void newGame();

    /*!
     * \brief closeGame
     */
    void closeGame();

    /*!
     * \brief help
     */
    void help();
};

#endif // MAINWINDOWSTARLIGHT_H
