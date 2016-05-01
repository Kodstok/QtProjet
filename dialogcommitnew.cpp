#include "dialogcommitnew.h"
#include "ui_dialogcommitnew.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <annonce.h>

DialogCommitNew::DialogCommitNew(QWidget *parent, std::vector<Annonce> *_ref_tab, QString _num, QString _code, QString _ville, QString _type, int _piece, double _surfaceT, double _surfaceH, QString _nom, QString _prenom, QString _mail, QString _tel, QString _typeV, double _prix, QString _titre, QString _descr, QString _image1, QString _image2, QString _image3, QString _image4) :
    QDialog(parent),
    ui(new Ui::DialogCommitNew)
{
    ui->setupUi(this);
    this->setModal(false);
    /* récupération des données de la page précédente */
    b_parent = parent;
    ref_tab = _ref_tab;
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

    ui->label_num->setText(num);
    ui->label_code->setText(code);
    ui->label_ville->setText(ville);
    ui->label_type->setText(type);
    ui->label_pieces->setNum(piece);
    ui->label_surfaceT->setNum(surfaceT);
    ui->label_surfaceH->setNum(surfaceH);
    ui->label_nom->setText(nom);
    ui->label_prenom->setText(prenom);
    ui->label_mail->setText(mail);
    ui->label_tel->setText(tel);
    ui->label_typeV->setText(typeV);
    ui->label_prix->setNum(prix);
    ui->label_titre->setText(titre);
    ui->label_descr->setText(descr);

    actualiseImgs(image1, image2, image3, image4);

    /* PushButton: Retour */
    QObject::connect(ui->pushButton_Return_3,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton_Valid_3,SIGNAL(clicked()),this,SLOT(validation()));

}

DialogCommitNew::~DialogCommitNew()
{
    delete ui;
}

void DialogCommitNew::actualiseImgs(QString file1, QString file2, QString file3, QString file4)
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

void DialogCommitNew::validation()
{

    if (num.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Adresse incomplète ! <strong>Veuillez préciser le numéro et la voie</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (code.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Adresse incomplète ! <strong>Veuillez préciser le code postal</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (ville.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Adresse incomplète ! <strong>Veuillez préciser la ville</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (surfaceT == 0)
    {
        QMessageBox::warning(this, "Information manquante !", "Surface du terrain inexistante ! <strong>Veuillez ajouter une surface totale</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (nom.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Informations sur le propriétaire incomplètes ! <strong>Veuillez donner un nom</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (prenom.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Informations sur le propriétaire incomplètes ! <strong>Veuillez donner un prénom</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (mail.isEmpty() && tel.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Informations sur le propriétaire incomplètes ! <strong>Veuillez donner une adresse E-Mail ou un numéro de téléphone</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (prix == 0)
    {
        QMessageBox::warning(this, "Information manquante !", "Prix inexistant ! <strong>Veuillez ajouter un prix</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    if (titre.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Titre de l'annonce inexistant ! <strong>Veuillez ajouter un titre</strong> <br>(retournez à l'étape 1/2 de la création de l'annonce).");
        return ;
    }

    Annonce newa;
    newa.num = num;
    newa.code = code;
    newa.ville = ville;
    newa.type = type;
    newa.piece = piece;
    newa.surfaceT = surfaceT;
    newa.surfaceH = surfaceH;
    newa.nom = nom;
    newa.prenom = prenom;
    newa.mail = mail;
    newa.tel = tel;
    newa.typeV = typeV;
    newa.prix = prix;
    newa.titre = titre;
    newa.descr = descr;
    newa.image1 = image1;
    newa.image2 = image2;
    newa.image3 = image3;
    newa.image4 = image4;

    ref_tab->push_back(newa);
    QMessageBox::information(NULL, "Information", "L'annonce: " +  titre + " a bien été enregistré");
    b_parent->close();
    close();

}
