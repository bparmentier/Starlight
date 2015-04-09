#ifndef DIALOGCONFIG_H
#define DIALOGCONFIG_H

#include <QDialog>

namespace Ui {
    class DialogConfig;
}

class DialogConfig : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    explicit DialogConfig(QWidget *parent = 0);

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    ~DialogConfig();

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    QString getNomFichier();

private:
    Ui::DialogConfig *ui;
    QString m_nomFichier;

private slots:

    /*!
     * \brief StarlightGame
     * \param nomFichier
     */
    void naviguer();
};

#endif // DIALOGCONFIG_H
