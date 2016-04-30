#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewa.h"
#include "dialogrecherche.h"
#include "annonce.h"
#include "xml_dom.h"
#include <stdio.h>
#include <vector>
#include <QtXml>
#include <QtGui>
#include <QMessageBox>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->actionAjouter,SIGNAL(triggered()),
                     this,SLOT(dialogAdd()));

    QObject::connect(ui->actionRech,SIGNAL(triggered()),
                     this,SLOT(dialogRech()));

    QObject::connect(ui->actionQuitter,SIGNAL(triggered()),
                     this,SLOT(quitMain()));


    /* création du tableau d'annonces */
    //ref_tab = tab_annonces;
    tab_annonces = new vector<Annonce>();


    /* ###################### main XML #########################*/

        QDomDocument dom("annonces");
        QFile xml_doc("annonces.xml");
        if(!xml_doc.open(QIODevice::ReadOnly))// Si l'on n'arrive pas à ouvrir le fichier XML.
        {
            QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
            //return;
        }

        if (!dom.setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
        {
                xml_doc.close();
                QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
                //return;
        }

        /* Récupération des éléments */
        QDomElement dom_element = dom.documentElement();
        QDomNode noeud = dom_element.firstChild();
        Annonce a;

        while(!noeud.isNull())// Tant que le nœud n'est pas vide.
        {
            QDomElement e = noeud.toElement();

            /* créastion de la nouvelle annonce à partir du fichier xml*/
            a.num = e.attribute("num");
            a.code = e.attribute("code");
            a.ville = e.attribute("ville");
            a.type = e.attribute("type");
            a.piece = e.attribute("piece").toInt();
            a.surfaceT = e.attribute("surfaceT").toDouble();
            a.surfaceH = e.attribute("surfaceH").toDouble();
            a.nom = e.attribute("nom");
            a.prenom = e.attribute("prenom");
            a.mail = e.attribute("mail");
            a.tel = e.attribute("tel");
            a.typeV = e.attribute("typeV");
            a.prix = e.attribute("prix").toDouble();
            a.titre = e.attribute("titre");
            a.descr = e.attribute("descr");
            a.image1 = e.attribute("image1");
            a.image2 = e.attribute("image2");
            a.image3 = e.attribute("image3");
            a.image4 = e.attribute("image4");

            /* ajouter la nouvelle annonce dans le vecteur */
            tab_annonces->push_back(a);

            //tab_annonces.push_back(a);
            //QMessageBox::information(NULL, "Information", "La rue est :<br />" + e.attribute("num"));
            noeud = noeud.nextSibling();
        }

    /* fermeture du fichier xml */
    xml_doc.close();

}

void MainWindow::dialogAdd()
{
    printf("Add\n");
    DialogNewA *d = new DialogNewA(this, tab_annonces);
    d->show();
}

void MainWindow::dialogRech()
{
    //test
    //QMessageBox::information(NULL, "Information", "table:<br />" + tab_annonces->at(2).num);

    printf("Recherche\n");
    DialogRecherche *r = new DialogRecherche(this);
    r->show();
}

void MainWindow::save()
{
/* ebauche de la fonction pour sauvgarder au formart xml
 * à la fin de l'utilisation du programe on écrit tout ce qu'il y a
 * dans le vecteur pos (les différentes possessions des gens) dans le fichier xml
 */
    QDomDocument doc( "MonDoc" );
    QDomElement root = doc.createElement( "possessions" );
    doc.appendChild( root );
    QDomElement p = doc.createElement("possession");
    p.setAttribute("prix",100);
    p.setAttribute("test","lol");
    root.appendChild(p);
    QFile file("/Users/Kodstok/TpQt/possessions.xml");
    if(!file.open(QIODevice::WriteOnly))
            QMessageBox::critical(this,"Erreur","Impossible d'écrire dans le document XML");


    QTextStream ts( &file );
    ts << doc.toString();
    file.close();
}

void MainWindow::quitMain()
{
    //QMessageBox::information(NULL, "Information", "lol");
    /* ecriture dans le XML */

    if (remove("annonces.xml") != 0)
    {
        QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
    }

    ofstream newfichier;
    newfichier.open("annonces.xml", ios::out);


    newfichier <<"<?xml version='1.0' encoding='UTF-8' standalone='yes'?>" << endl;
    newfichier <<"<bloc_annonces>" << endl;
    newfichier <<"</bloc_annonces>" << endl;
    newfichier.close();

    QDomDocument dom("annonces");
    QFile doc_xml("annonces.xml");
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

    // boucle
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


        QFile fichier("annonces.xml");
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




    QCoreApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
