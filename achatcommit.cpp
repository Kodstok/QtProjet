#include "mainwindow.h"
#include "dialogdetails.h"
#include "achatcommit.h"
#include "objeta.h"
#include "annonce.h"
#include <ctime>
#include <time.h>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QtXml>
#include <vector>

AchatCommit::AchatCommit(DialogDetails *parent, int _id, std::vector<Annonce> *_ref_tab) : QDialog(parent),
    ui(new Ui::AchatCommit)
{
    ui->setupUi(this);

    b_parent = parent;
    id = _id;
    tab_annonces = _ref_tab;

    QObject::connect(ui->pushRetour,SIGNAL(clicked()),
                     this,SLOT(close()));

    QObject::connect(ui->pushConclure,SIGNAL(clicked()),
                     this,SLOT(slotFinalConclure()));

    ui->label_titre->setText(tab_annonces->at(id).titre);

    if (!(tab_annonces->at(id).typeV.compare("Vente")))
    {
        ui->spinBoxDuree->close();
        ui->label_6->close();
    }

}

void AchatCommit::slotFinalConclure()
{

    QString nom = ui->lineEdit_Name_Prop->text();
    QString prenom = ui->lineEdit_Firstname->text();
    QString mail = ui->lineEdit_Mail->text();
    QString tel = ui->lineEdit_Tel->text();
    QString duree;
    int d;

    if (tab_annonces->at(id).typeV.compare("Location") == 0)
    {
        d = ui->spinBoxDuree->value();
        duree = QString::number(d);
    }

    if (nom.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Nom de l'acquéreur manquant ! <strong>Veuillez préciser au moins un nom, un prénom et au minimum un moyen de contact.</strong> <br>");
        return ;
    }

    if (prenom.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Prénom de l'acquéreur manquant ! <strong>Veuillez préciser au moins un nom, un prénom et au minimum un moyen de contact.</strong> <br>");
        return ;
    }

    if (mail.isEmpty() && tel.isEmpty())
    {
        QMessageBox::warning(this, "Information manquante !", "Adresse Mail ou Numéro de téléphone de l'acquéreur manquant ! <strong>Veuillez préciser au moins un nom, un prénom et au minimum un moyen de contact.</strong> <br>");
        return ;
    }

    if (tab_annonces->at(id).typeV.compare("Location") == 0)
    {
        if (duree.compare("0") == 0)
        {
            QMessageBox::warning(this, "Information manquante !", "Durée de location nulle ! <strong>Veuillez préciser le temps de location (en mois) " + duree + ".</strong> <br>");
            return ;
        }
    }

    /*####### Ecrire dans stats.xml #######*/

    QDomDocument dom("stats_conlus");
    QFile doc_xml(cheminstats);
    if(!doc_xml.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
        doc_xml.close();
        //return;
    }
    if(!dom.setContent(&doc_xml))
    {
        QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
        doc_xml.close();
        //return;
    }
    doc_xml.close();

    QDomElement docElem = dom.documentElement();

    /* boucle d'écriture */
    QDomElement write_elem;
    int i = id;

    write_elem = dom.createElement("annonce");

    write_elem.setAttribute("id", i);
    write_elem.setAttribute("num", tab_annonces->at(i).num );
    write_elem.setAttribute("code", tab_annonces->at(i).code );
    write_elem.setAttribute("ville", tab_annonces->at(i).ville );
    write_elem.setAttribute("type", tab_annonces->at(i).type );
    write_elem.setAttribute("piece", tab_annonces->at(i).piece );
    write_elem.setAttribute("surfaceT", tab_annonces->at(i).surfaceT );
    write_elem.setAttribute("surfaceH", tab_annonces->at(i).surfaceH );
    write_elem.setAttribute("nom", tab_annonces->at(i).nom );
    write_elem.setAttribute("prenom", tab_annonces->at(i).prenom );
    write_elem.setAttribute("mail", tab_annonces->at(i).mail );
    write_elem.setAttribute("tel", tab_annonces->at(i).tel );
    write_elem.setAttribute("typeV", tab_annonces->at(i).typeV );
    write_elem.setAttribute("prix", tab_annonces->at(i).prix );
    write_elem.setAttribute("titre", tab_annonces->at(i).titre );
    write_elem.setAttribute("descr", tab_annonces->at(i).descr );
    write_elem.setAttribute("image1", tab_annonces->at(i).image1 );
    write_elem.setAttribute("image2", tab_annonces->at(i).image2 );
    write_elem.setAttribute("image3", tab_annonces->at(i).image3 );
    write_elem.setAttribute("image4", tab_annonces->at(i).image4 );
    write_elem.setAttribute("nom_acq", nom );
    write_elem.setAttribute("prenom_acq", prenom );
    write_elem.setAttribute("mail_acq", mail );
    write_elem.setAttribute("tel_acq", tel );

    if (tab_annonces->at(id).typeV.compare("Location") == 0)
    {
        write_elem.setAttribute("duree_loc", duree );
    }
    else
    {
        write_elem.setAttribute("duree_loc", "" );
    }

    /* date d'aquisition */
    time_t _time;
    struct tm timeInfo;
    char format[32];
    time(&_time);
    localtime_r( &_time,&timeInfo);
    strftime(format, 32, "%Y-%m-%d %H-%M", &timeInfo);

    QString date_s = format;
    write_elem.setAttribute("date_acq", date_s );


    docElem.appendChild(write_elem);
    QString write_doc = dom.toString();


    QFile fichier(cheminstats);
    if(!fichier.open(QIODevice::WriteOnly))
    {
        fichier.close();
        QMessageBox::critical(this,"Erreur","Impossible d'écrire dans le document XML");
        return;
    }
    QTextStream stream(&fichier);
    stream << write_doc;

    fichier.close();


    QMessageBox::information(NULL, "Information", "L'offre a été finalisée. Le nouveau propriétaire est " + nom + " " + prenom + ".");
    tab_annonces->erase(tab_annonces->begin() + id);
    b_parent->d_parent->a_parent->refresh_annonces();
    /* fermeture de la fenetre */
    b_parent->close();
    this->close();
}

AchatCommit::~AchatCommit()
{
}
