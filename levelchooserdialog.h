#ifndef LEVELCHOOSERDIALOG_H
#define LEVELCHOOSERDIALOG_H

#include <QDialog>

namespace Ui {
class LevelChooserDialog;
}

class LevelChooserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LevelChooserDialog(QWidget *parent = 0);
    ~LevelChooserDialog();
    int getLevel();

private:
    Ui::LevelChooserDialog *ui;
    int m_level;

private slots:
    void setLevel(int level);
};

#endif // LEVELCHOOSERDIALOG_H
