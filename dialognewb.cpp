#include "DialogNewB.h"
#include "DialogNewA.h"
#include "dialogcommitnew.h"
#include "ui_dialognewB.h"
#include "ui_dialognewA.h"
#include "ui_dialogcommitnew.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

DialogNewB::DialogNewB(QWidget *parent, QString _num, QString _code, QString _ville, QString _type, int _piece, double _surfaceT, double _surfaceH, QString _nom, QString _prenom, QString _mail, QString _tel, QString _typeV, double _prix, QString _titre, QString _descr, QString _image1, QString _image2, QString _image3, QString _image4) :
    QDialog(parent),
    ui(new Ui::DialogNewB)
{
    ui->setupUi(this);

    /* récupération des données entre les pages */
    num = _num;
    code = _code;
    ville = _ville;
    type = _type;
    piece = _piece;
    surfaceT = _surfaceT;
    surfaceH = _surfaceH;
    nom = _nom;
    prenom = _prenom;
    mail = _mail;
    tel = _tel;
    typeV = _typeV;
    prix = _prix;
    titre = _titre;
    descr = _descr;
    image1 = _image1;
    image2 = _image2;
    image3 = _image3;
    image4 = _image4;

    /* reaffichage des données entre les pages */
    ui->lineEdit_Titre->insert(titre);
    ui->plainTextEdit_Description->insertPlainText(descr);
    actualiseImgs(image1, image2, image3, image4);


    /* PushButtons: Insérer l'image 1, 2, 3 et 4 */
    QObject::connect(ui->pushButton_ImgSelect,SIGNAL(clicked()),this,SLOT(addImg1()));
    QObject::connect(ui->pushButton_ImgSelect_2,SIGNAL(clicked()),this,SLOT(addImg2()));
    QObject::connect(ui->pushButton_ImgSelect_3,SIGNAL(clicked()),this,SLOT(addImg3()));
    QObject::connect(ui->pushButton_ImgSelect_4,SIGNAL(clicked()),this,SLOT(addImg4()));

    /* PushButton: Précédent */
    QObject::connect(ui->pushButton_Precedent_2,SIGNAL(clicked()),this,SLOT(previous()));

    /* PushButton: Valider */
    QObject::connect(ui->pushButton_Valid_2,SIGNAL(clicked()),this,SLOT(add()));

    /* PushButton: Annuler */
    QObject::connect(ui->pushButton_Annuler_2,SIGNAL(clicked()),this,SLOT(close()));

}


/* Retour à la page précédente */
void DialogNewB::previous()
{
    /* sauvegarde des données entre les pages */
    titre = ui->lineEdit_Titre->text();
    descr = ui->plainTextEdit_Description->toPlainText();

    DialogNewA *a = new DialogNewA(this, num, code, ville, type, piece, surfaceT, surfaceH, nom, prenom, mail, tel, typeV, prix, titre, descr, image1, image2, image3, image4);
    a->show();
    this->close();
}

/* fenetre de validation */
void DialogNewB::add()
{
    /* sauvegarde des données entre les pages */
    titre = ui->lineEdit_Titre->text();
    descr = ui->plainTextEdit_Description->toPlainText();
    DialogCommitNew *c = new DialogCommitNew(this, num, code, ville, type, piece, surfaceT, surfaceH, nom, prenom, mail, tel, typeV, prix, titre, descr, image1, image2, image3, image4);
    c->setModal(true);
    c->show();
}


/* selectionner de nouvelles images */
void DialogNewB::addImg1()
{
    /* fonction appeler quand on clicque sur le bouton choisir une image */
    QString file = QFileDialog::getOpenFileName(this,"Images","/Users","Images (*.png *.xpm *.jpg)");
    int w = ui->label_img->width();// on veut les dimmension actuel du label
    int h = ui->label_img->height();
    QPixmap *qp = new QPixmap(file);
    ui->label_img->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio)); // on rajoute la photo au label pour la visualiser
    image1 = file;
}

void DialogNewB::addImg2()
{
    QString file = QFileDialog::getOpenFileName(this,"Images","/Users","Images (*.png *.xpm *.jpg)");
    int w = ui->label_img_2->width();
    int h = ui->label_img_2->height();
    QPixmap *qp = new QPixmap(file);
    ui->label_img_2->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    image2 = file;
}

void DialogNewB::addImg3()
{
    QString file = QFileDialog::getOpenFileName(this,"Images","/Users","Images (*.png *.xpm *.jpg)");
    int w = ui->label_img_3->width();
    int h = ui->label_img_3->height();
    QPixmap *qp = new QPixmap(file);
    ui->label_img_3->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    image3 = file;
}

void DialogNewB::addImg4()
{
    QString file = QFileDialog::getOpenFileName(this,"Images","/Users","Images (*.png *.xpm *.jpg)");
    int w = ui->label_img_4->width();
    int h = ui->label_img_4->height();
    QPixmap *qp = new QPixmap(file);
    ui->label_img_4->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    image4 = file;
}

/* actualisation des images */
void DialogNewB::actualiseImgs(QString file1, QString file2, QString file3, QString file4)
{
    // on veut les dimmension actuel du label
    int w ;
    int h ;

    /* Si l'image n a été donné précédement, on l'affiche */

    if (!(file1.isEmpty()))
    {
        w = ui->label_img->width();
        h = ui->label_img->height();
        QPixmap *qp = new QPixmap(file1);
        ui->label_img->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    }

    if (!(file2.isEmpty()))
    {
        w = ui->label_img_2->width();
        h = ui->label_img_2->height();
        QPixmap *qp = new QPixmap(file2);
        ui->label_img_2->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    }

    if (!(file3.isEmpty()))
    {
        w = ui->label_img_3->width();
        h = ui->label_img_3->height();
        QPixmap *qp = new QPixmap(file3);
        ui->label_img_3->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    }

    if (!(file4.isEmpty()))
    {
        w = ui->label_img_4->width();
        h = ui->label_img_4->height();
        QPixmap *qp = new QPixmap(file4);
        ui->label_img_4->setPixmap(qp->scaled(w,h,Qt::KeepAspectRatio));
    }
}




DialogNewB::~DialogNewB()
{
    delete ui;
}
