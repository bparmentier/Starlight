#ifndef DIALOGCONFIG_H
#define DIALOGCONFIG_H

#include <QDialog>

namespace Ui {
    class DialogConfig;
}

/*!
 * \brief The DialogConfig class
 */
class DialogConfig : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief Construit un DialogConfig avec le *parent* donné en paramètre.
     * \param parent
     */
    explicit DialogConfig(QWidget *parent = 0);

    ~DialogConfig();

    /*!
     * \brief Retourne le nom du fichier de carte.
     * \return
     */
    QString getFileName();

private:

    Ui::DialogConfig *ui;
    QString m_fileName;

private slots:

    void browse();
};

#endif // DIALOGCONFIG_H
