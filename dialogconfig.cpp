#include "dialogconfig.h"
#include "ui_dialogconfig.h"
#include <qfiledialog.h>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent), ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    connect(ui->navig, SIGNAL(clicked()), this, SLOT(naviguer()));
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
    m_nomFichier = QFileDialog::getOpenFileName(this,"Choisir un fichier .map");
    if(m_nomFichier == nullptr){
        ui->fileName->setText("(rien)");
    }else{
        QFileInfo infoFichier {m_nomFichier};
        ui->fileName->setText(infoFichier.fileName());
    }
}
