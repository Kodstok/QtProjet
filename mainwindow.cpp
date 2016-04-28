#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewa.h"
#include "dialogrecherche.h"
#include "annonce.h"
#include "xml_dom.h"
#include <vector>
#include <QtXml>
#include <QtGui>
#include <QMessageBox>

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
                     qApp,SLOT(quit()));

    /* création du tableau d'annonces */
    //vector<Annonce> tab_annonces;



    /* ###################### main XML #########################*/

    QDomDocument *dom = new QDomDocument("types");
        QFile xml_doc("types.xml");
        if(!xml_doc.open(QIODevice::ReadOnly))// Si l'on n'arrive pas à ouvrir le fichier XML.
        {
            QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
            return;
        }

        if (!dom->setContent(&xml_doc)) // Si l'on n'arrive pas à associer le fichier XML à l'objet DOM.
        {
                xml_doc.close();
                QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
                return;
        }

    xml_doc.close(); // Dans tous les cas, on doit fermer le document XML : on n'en a plus besoin, tout est compris dans l'objet DOM.
}

void MainWindow::dialogAdd()
{
    printf("Add\n");
    DialogNewA *d = new DialogNewA(this);
    d->show();
}

void MainWindow::dialogRech()
{
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

MainWindow::~MainWindow()
{
    delete ui;
}
