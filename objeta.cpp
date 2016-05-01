#include "mainwindow.h"
#include "objeta.h"
#include "annonce.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>

ObjetA::ObjetA(QWidget *parent, int _id, std::vector<Annonce> *_ref_tab) : QDialog(parent)
{
    id_a = _id;
    tab_annonces = _ref_tab;
}


ObjetA::~ObjetA()
{
}
