#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectSignals();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectSignals()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionQuit, &QAction::triggered, &QCoreApplication::quit);
}

void MainWindow::openFile()
{
    // TODO
}
