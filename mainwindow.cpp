#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewa.h"
#include <QtXml>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButtonAdd,SIGNAL(clicked()),
                     this,SLOT(dialogAdd()));
    QObject::connect(ui->pushButtonQuit,SIGNAL(clicked()),
                     qApp,SLOT(quit()));
}

void MainWindow::dialogAdd()
{
    DialogNewA *d = new DialogNewA(this);
    d->show();
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
