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
    QObject::connect(ui->pushRecherche,SIGNAL(clicked()),
                     this,SLOT(recherche()));
}

void DialogRecherche::recherche()
{
    MainWindow *w = (MainWindow*)this->parent();
    bool test = true;
    std::vector<Annonce> *tab_recherche=new std::vector<Annonce>();
    for(int i = 0 ; i< (int)w->tab_annonces->size();i++)
    {
        test=true;
        Annonce a = w->tab_annonces->at(i);
        if(ui->comboBoxType->currentText()!= a.type)
            test = false;printf("Type\n");
        if(ui->comboBox_vente_loc->currentText() != "" &&ui->comboBox_vente_loc->currentText()!=a.typeV)
            test = false;printf("vente_loc\n");
        if(ui->doubleSpinBoxsSquareMeter_habSup->value()!=0&&(ui->doubleSpinBoxsSquareMeter_habInf->value()>a.surfaceH || ui->doubleSpinBoxsSquareMeter_habSup->value() < a.surfaceH))
            test = false;printf("squareMetterHab\n");
        if(ui->doubleSpinBoxsSquareMeter_terrainSup->value()!=0&&(ui->doubleSpinBoxsSquareMeter_terrainInf->value()>a.surfaceT|| ui->doubleSpinBoxsSquareMeter_terrainSup->value()<a.surfaceT))
            test=false;printf("SquareMetterTerrain\n");
        if(ui->lineEdit_Ville->text() !=""&&ui->lineEdit_Ville->text() != a.ville)
            test=false;printf("Ville\n");
        if(ui->spinBoxPrixSup->value()!=0&&(ui->spinBoxPrixInf->value()>a.prix||ui->spinBoxPrixSup->value()<a.prix))
            test=false;printf("Prix\n");
        if(ui->spinBoxNumberRoomSup->value()!=0&&(ui->spinBoxNumberRoomInf->value()>a.piece||ui->spinBoxNumberRoomSup->value()<a.piece))
            test=false;printf("Room\n");
        if(ui->lineEdit_ZipCode->text()!=""&&ui->lineEdit_ZipCode->text()!=a.code)
            test=false;printf("ZIP\n");
        if(test)
            tab_recherche->push_back(a);

        printf("\n");



    }
    w->reset_annonces();
    w->affiche_annonces(tab_recherche);
    this->close();
}


DialogRecherche::~DialogRecherche()
{
    delete ui;
}
