#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewa.h"
#include "dialogrecherche.h"
#include "annonce.h"
#include "dialogdetails.h"
#include "objeta.h"
#include "xml_dom.h"
#include <stdio.h>
#include <vector>
#include <QtXml>
#include <QtGui>
#include <QMessageBox>
#include <QPushButton>
#include <fstream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPalette>
#include <QPixmap>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* connection de la barre d'outils */
    QObject::connect(ui->actionAjouter,SIGNAL(triggered()),
                     this,SLOT(dialogAdd()));

    QObject::connect(ui->actionRech,SIGNAL(triggered()),
                     this,SLOT(dialogRech()));

    QObject::connect(ui->actionQuitter,SIGNAL(triggered()),
                     this,SLOT(quitMain()));

    QObject::connect(ui->actionRefresh,SIGNAL(triggered()),
                     this,SLOT(slot_refresh()));



    /* création du tableau d'annonces */
    tab_annonces = new vector<Annonce>();


    /* ###################### main XML #########################*/

        QDomDocument dom("annonces");
        QFile xml_doc(chemin);
        if(!xml_doc.open(QIODevice::ReadOnly))// Si l'on n'arrive pas à ouvrir le fichier XML.
        {
            QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
            return;
        }

        if (!dom.setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
        {
                xml_doc.close();
                QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
                return;
        }

        /* Récupération des éléments */
        QDomElement dom_element = dom.documentElement();
        QDomNode noeud = dom_element.firstChild();
        Annonce a;

        while(!noeud.isNull())// Tant que le nœud n'est pas vide.
        {
            QDomElement e = noeud.toElement();

            /* création de la nouvelle annonce à partir du fichier xml*/
            a.num = (QString) e.attribute("num");
            a.code = (QString) e.attribute("code");
            a.ville = (QString) e.attribute("ville");
            a.type = (QString) e.attribute("type");
            a.piece = e.attribute("piece").toInt();
            a.surfaceT = e.attribute("surfaceT").toDouble();
            a.surfaceH = e.attribute("surfaceH").toDouble();
            a.nom = (QString) e.attribute("nom");
            a.prenom = (QString) e.attribute("prenom");
            a.mail = (QString) e.attribute("mail");
            a.tel = (QString) e.attribute("tel");
            a.typeV = (QString) e.attribute("typeV");
            a.prix = e.attribute("prix").toDouble();
            a.titre = (QString) e.attribute("titre");
            a.descr = (QString) e.attribute("descr");
            a.image1 = (QString) e.attribute("image1");
            a.image2 = (QString) e.attribute("image2");
            a.image3 = (QString) e.attribute("image3");
            a.image4 = (QString) e.attribute("image4");

            /* ajouter la nouvelle annonce dans le vecteur */
            tab_annonces->push_back(a);

            noeud = noeud.nextSibling();
        }

    /* fermeture du fichier xml */
    xml_doc.close();

    /* affichage */
    affiche_annonces(tab_annonces);
}


/* ###################### Scroll Area ######################### */

void MainWindow::affiche_annonces(std::vector<Annonce> *tab_annonces)
{
    scroll_annonces = new QScrollArea();
    setCentralWidget(scroll_annonces);
    QWidget *contenu = new QWidget;
    QVBoxLayout *mLayout = new QVBoxLayout();
    contenu->setLayout(mLayout);

    /* boucle, pour afficher toutes las annonces du vecteur donné*/
    int i;
    for (i=0; i< (int) tab_annonces->size(); i++)
    {
        QWidget *frame_annonce = new QWidget();
        frame_annonce->setFixedHeight(200);
        frame_annonce->setFixedWidth(this->width()-50);

        QVBoxLayout *vbox = new QVBoxLayout(frame_annonce);
        QHBoxLayout *hbox = new QHBoxLayout();
        QVBoxLayout *vbox_ville = new QVBoxLayout();
        QVBoxLayout *vbox_prix = new QVBoxLayout();

        /* labels */
        QLabel *t_titre = new QLabel(tab_annonces->at(i).titre);
        QLabel *t_image = new QLabel();
        QPixmap *pixmap_img = new QPixmap(tab_annonces->at(i).image1);
             t_image->setPixmap(pixmap_img->scaled(150,150,Qt::KeepAspectRatio));

        QLabel *t_ville = new QLabel(tab_annonces->at(i).ville);
        QLabel *t_bien = new QLabel(tab_annonces->at(i).type);
        QLabel *t_offre = new QLabel(tab_annonces->at(i).typeV);

        double prix_c = tab_annonces->at(i).prix;
        QString prix_s = QString::number(prix_c);

        QLabel *t_prix = new QLabel(prix_s);
        QPushButton *boutonA = new QPushButton("Voir l'annonce");

        /* Labels fixes (en gras) */
        QLabel *f_ville = new QLabel("<b>Ville:</b>");
        QLabel *f_bien = new QLabel("<b>Type de bien:</b>");
        QLabel *f_offre = new QLabel("<b>Type d'offre:</b>");
        QLabel *f_prix = new QLabel("<b>Prix (euros):</b>");

        /*ligne de séparation entre les annonces */
        QFrame *ligne = new QFrame();
        ligne->setFixedWidth(1000);
        ligne->setFixedHeight(4);
        QPalette palette = ligne->palette();
        palette.setColor( backgroundRole(), QColor( 63, 63, 63 ) );
        ligne->setPalette( palette );
        ligne->setAutoFillBackground( true );

        /* Minor Verticalboxes */
        vbox_ville->addWidget(f_ville);
        vbox_ville->addWidget(t_ville);
        vbox_ville->addWidget(f_bien);
        vbox_ville->addWidget(t_bien);
        vbox_prix->addWidget(f_offre);
        vbox_prix->addWidget(t_offre);
        vbox_prix->addWidget(f_prix);
        vbox_prix->addWidget(t_prix);

        /* Horizontalbox */
        hbox->addWidget(t_image);
        hbox->addLayout(vbox_ville);
        hbox->addLayout(vbox_prix);
        hbox->addWidget(boutonA);

        /* Verticalbox */
        vbox->addWidget(t_titre);
        vbox->addLayout(hbox);
        vbox->addWidget(ligne);

        /* annonce complète */
        mLayout->addWidget(frame_annonce);

        /* connection au bouton de visualisation de l'annonce */
        ObjetA *A = new ObjetA(this, i, tab_annonces);
        QObject::connect(boutonA,SIGNAL(clicked()), A, SLOT(viewAnnonce()));
    }

    /* mise dans le scroll */
    scroll_annonces->setWidget(contenu);
    scroll_annonces->show();
}



/* Slot de visualisation d'annonce */
void ObjetA::viewAnnonce()
{
    DialogDetails *det = new DialogDetails(this, id_a, tab_annonces);
    det->show();
}


/* Fonction de suffression du scrollarea */
void MainWindow::reset_annonces()
{
    delete scroll_annonces;
}


/* Fonction de rafraichisement */
void MainWindow::refresh_annonces()
{
    reset_annonces();
    affiche_annonces(tab_annonces);
}


/* slot quand on appuie sur le bouton rafraîchir */
void MainWindow::slot_refresh()
{
    refresh_annonces();
}


void MainWindow::dialogAdd()
{
    printf("Add\n");
    DialogNewA *d = new DialogNewA(this, this);
    d->show();
}


/* création de la fenetre rechercher */
void MainWindow::dialogRech()
{
    printf("Recherche\n");
    DialogRecherche *r = new DialogRecherche(this);
    r->show();
}


/* Sauvegarder et quitter */
void MainWindow::quitMain()
{
    /* ecriture dans le XML */

    if (remove(chemin.toStdString().c_str()) != 0)
    {
        QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
    }

    ofstream newfichier;
    newfichier.open(chemin.toStdString(), ios::out);

    newfichier <<"<?xml version='1.0' encoding='ISO-8859-1' standalone='yes'?>" << endl;
    newfichier <<"<bloc_annonces>" << endl;
    newfichier <<"</bloc_annonces>" << endl;
    newfichier.close();

    QDomDocument dom("annonces");
    QFile doc_xml(chemin);
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
    int i;
    for (i=0; i < (int)tab_annonces->size(); i++)
    {
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

        docElem.appendChild(write_elem);
        QString write_doc = dom.toString();


        QFile fichier(chemin);
        if(!fichier.open(QIODevice::WriteOnly))
        {
            fichier.close();
            QMessageBox::critical(this,"Erreur","Impossible d'écrire dans le document XML");
            return;
        }
        QTextStream stream(&fichier);
        stream << write_doc;

        fichier.close();
    }

    /* Quitter l'application */
    QCoreApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
