#include "mainwindow.h"
#include "dialogrecherche.h"
#include "ui_dialogrecherche.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

DialogRecherche::DialogRecherche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRecherche)
{
    ui->setupUi(this);
}


DialogRecherche::~DialogRecherche()
{
    delete ui;
}
