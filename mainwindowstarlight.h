#ifndef MAINWINDOWSTARLIGHT_H
#define MAINWINDOWSTARLIGHT_H

#include <string>
#include <QMainWindow>
#include "starlight/level.h"
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
    nvs::Level *m_level = nullptr;
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

    /*!
     * \brief Lit le contenu du fichier de carte donné par *fileName* et crée un
     * nouveau nvs::Level
     * \param fileName le chemin vers le fichier de carte
     */
    void readMap(const std::string &fileName);

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
