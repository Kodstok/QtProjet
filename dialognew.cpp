#include "dialognew.h"
#include "ui_dialognew.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

DialogNew::DialogNew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNew)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton_ImgSelect,SIGNAL(clicked()),
    this,SLOT(addImg()));
    QObject::connect(ui->pushButton_Valid,SIGNAL(clicked()),
                      this,SLOT(add()));
    MainWindow  *p = (MainWindow*) parent;
    for(int i = 0 ; i < MAX ; i++)// ajout de chaque type pour la combobox
    {
        ui->comboBoxType->addItem(p->types[i]);
    }

}

void DialogNew::add()
{

}

void DialogNew::addImg()
{
    /* fonction appeler quand on clicque sur le bouton choisir une image
     */
    QString file = QFileDialog::getOpenFileName(this,"Images","/Users","Images (*.png *.xpm *.jpg)");
    int w = ui->label_img->width();// on veut les dimmension actuel du label
    int h = ui->label_img->height();
    QPixmap *qp = new QPixmap(file);
    ui->label_img->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio)); // on rajoute la photo au label pour la visualiser
}

DialogNew::~DialogNew()
{
    delete ui;
}
