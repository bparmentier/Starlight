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
    explicit DialogConfig(QWidget *parent = 0);
    ~DialogConfig();
    QString getNomFichier();

private:
    Ui::DialogConfig *ui;
    QString nomFichier_;

private slots:
    void naviguer();
};

#endif // DIALOGCONFIG_H
