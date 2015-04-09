#include "dialogconfig.h"
#include "ui_dialogconfig.h"
#include <qfiledialog.h>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent), ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    connect(ui->navig, &QPushButton::clicked, this, &DialogConfig::naviguer);
}

DialogConfig::~DialogConfig()
{
    delete ui;
    ui = nullptr;
}

QString DialogConfig::getNomFichier()
{
    return m_nomFichier;
}

void DialogConfig::naviguer()
{
    QString nomFichier = QFileDialog::getOpenFileName(this,
                                                tr("Choisir un fichier"),
                                                ".",
                                                tr("Niveau (*.map *.mapl);;Tous les fichiers (*)"));
    if (!nomFichier.isEmpty()) {
        QFileInfo infoFichier {nomFichier};
        ui->fileName->setText(infoFichier.fileName());
        m_nomFichier = nomFichier;
    }
}
