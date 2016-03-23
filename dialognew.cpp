#include "dialognew.h"
#include "ui_dialognew.h"
#include <QtXml>
#include "mainwindow.h"
#include <QFileDialog>

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_ImgSelect,SIGNAL(clicked()),
    this,SLOT(addImg()));
    MainWindow  *p = (MainWindow*) parent;
    for(int i = 0 ; i < MAX ; i++)
    {
        ui->comboBoxType->addItem(p->types[i]);
    }

}

void DialogNew::addImg()
{
    QString file = QFileDialog::getOpenFileName(this,"Images","/Users","Images (*.png *.xpm *.jpg)");
    int w = ui->label_img->width();
    int h = ui->label_img->height();
    QPixmap *qp = new QPixmap(file);
    ui->label_img->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
}

DialogNew::~DialogNew()
{
    delete ui;
}
