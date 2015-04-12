#include "levelchooserdialog.h"
#include "ui_levelchooserdialog.h"

LevelChooserDialog::LevelChooserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelChooserDialog),
    m_level(1)
{
    ui->setupUi(this);
    setWindowTitle("Niveau");
    connect(ui->niveauComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setLevel(int)));
}

LevelChooserDialog::~LevelChooserDialog()
{
    delete ui;
}

int LevelChooserDialog::getLevel()
{
    return m_level;
}

void LevelChooserDialog::setLevel(int level)
{
    this->m_level = level + 1;
}
