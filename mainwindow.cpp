#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognew.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonAdd,SIGNAL(clicked()),
                     this,SLOT(dialogAdd()));
}

void MainWindow::dialogAdd()
{
    DialogNew *d = new DialogNew(this);
    d->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
