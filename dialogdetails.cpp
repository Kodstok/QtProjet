#include "mainwindow.h"
#include "dialogdetails.h"
#include "objeta.h"
#include "annonce.h"
#include "achatcommit.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

DialogDetails::DialogDetails(ObjetA *parent, int _id, std::vector<Annonce> *_ref_tab) : QDialog(parent),
    ui(new Ui::DialogDetails)
{
    ui->setupUi(this);
    this->setModal(false);
    d_parent = parent;
    id = _id;
    tab_annonces = _ref_tab;

    QObject::connect(ui->pushRetour,SIGNAL(clicked()),
                     this,SLOT(close()));

    QObject::connect(ui->pushConclure,SIGNAL(clicked()),
                     this,SLOT(slotConclure()));


    ui->label_num->setText(tab_annonces->at(id).num);
    ui->label_code->setText(tab_annonces->at(id).code);
    ui->label_ville->setText(tab_annonces->at(id).ville);
    ui->label_type->setText(tab_annonces->at(id).type);
    ui->label_pieces->setNum(tab_annonces->at(id).piece);
    ui->label_surfaceT->setNum(tab_annonces->at(id).surfaceT);
    ui->label_surfaceH->setNum(tab_annonces->at(id).surfaceH);
    ui->label_nom->setText(tab_annonces->at(id).nom);
    ui->label_prenom->setText(tab_annonces->at(id).prenom);
    ui->label_mail->setText(tab_annonces->at(id).mail);
    ui->label_tel->setText(tab_annonces->at(id).tel);
    ui->label_typeV->setText(tab_annonces->at(id).typeV);
    ui->label_prix->setNum(tab_annonces->at(id).prix);
    ui->label_titre->setText(tab_annonces->at(id).titre);
    ui->plainTextEdit_descr->insertPlainText(tab_annonces->at(id).descr);
    ui->plainTextEdit_descr->setReadOnly(true);

    actualiseImgs(tab_annonces->at(id).image1, tab_annonces->at(id).image2, tab_annonces->at(id).image3, tab_annonces->at(id).image4);
}


void DialogDetails::actualiseImgs(QString file1, QString file2, QString file3, QString file4)
{
    /* on veut les dimmension actuel du label */
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


void DialogDetails::slotConclure()
{
    AchatCommit *ach = new AchatCommit(this, id, tab_annonces);
    ach->show();
    //QMessageBox::information(NULL, "Information", "test");
}

DialogDetails::~DialogDetails()
{
}
