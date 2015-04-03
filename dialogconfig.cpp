#include "dialogconfig.h"
#include "ui_dialogconfig.h"
#include <qfiledialog.h>

DialogConfig::DialogConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfig)
{
    ui->setupUi(this);
    connect(ui->navig, SIGNAL(clicked()), this, SLOT(naviguer()));
}

DialogConfig::~DialogConfig()
{
    delete ui;
}

QString DialogConfig::getNomFichier(){
    return nomFichier_;
}

void DialogConfig::naviguer(){
    nomFichier_ = QFileDialog::getOpenFileName(this,"Choisir un fichier .map");
    if(nomFichier_ == nullptr){
        ui->fileName->setText("(rien)");
    }else{
        QFileInfo infoFile {nomFichier_};
        ui->fileName->setText(infoFile.fileName());
    }
}
