#include "DialogNewB.h"
#include "DialogNewA.h"
#include "ui_dialognewB.h"
#include "ui_dialognewA.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

DialogNewA::DialogNewA(QWidget *parent, MainWindow *_mw, QString _num, QString _code, QString _ville, QString _type, int _piece, double _surfaceT, double _surfaceH, QString _nom, QString _prenom, QString _mail, QString _tel, QString _typeV, double _prix, QString _titre, QString _descr, QString _image1, QString _image2, QString _image3, QString _image4) :
    QDialog(parent),
    ui(new Ui::DialogNewA)
{
    ui->setupUi(this);

    /* récupération des données entre les pages */
    mw = _mw;
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
    ui->lineEdit_Adress->insert(num);
    ui->lineEdit_ZipCode->insert(code);
    ui->lineEdit_City->insert(ville);
    ui->comboBoxType->setCurrentText(type);
    ui->spinBoxNumberRoom->setValue(piece);
    ui->doubleSpinBoxsSquareMeter_terrain->setValue(surfaceT);
    ui->doubleSpinBoxsSquareMeter->setValue(surfaceH);
    ui->lineEdit_Name_Prop->insert(nom);
    ui->lineEdit_Firstname->insert(prenom);
    ui->lineEdit_Mail->insert(mail);
    ui->lineEdit_Tel->insert(tel);
    ui->comboBox_vente_loc->setCurrentText(typeV);
    ui->doubleSpinBox_prix->setValue(prix);


    /* PushButton: Annuler */
    QObject::connect(ui->pushButton_Annuler,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton_Suivant,SIGNAL(clicked()),this,SLOT(suivantNew()));

}

void DialogNewA::suivantNew()
{
    /* sauvegarde des données entre les pages */
    num = ui->lineEdit_Adress->text();
    code = ui->lineEdit_ZipCode->text();
    ville = ui->lineEdit_City->text();
    type = ui->comboBoxType->currentText();
    piece = ui->spinBoxNumberRoom->value();
    surfaceT = ui->doubleSpinBoxsSquareMeter_terrain->value();
    surfaceH = ui->doubleSpinBoxsSquareMeter->value();
    nom = ui->lineEdit_Name_Prop->text();
    prenom = ui->lineEdit_Firstname->text();
    mail = ui->lineEdit_Mail->text();
    tel = ui->lineEdit_Tel->text();
    typeV = ui->comboBox_vente_loc->currentText();
    prix = ui->doubleSpinBox_prix->value();

    DialogNewB *b = new DialogNewB(this, mw, num, code, ville, type, piece, surfaceT, surfaceH, nom, prenom, mail, tel, typeV, prix, titre, descr, image1, image2, image3, image4);
    b->show();
    this->close();
}


DialogNewA::~DialogNewA()
{
    delete ui;
}
