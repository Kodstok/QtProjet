#ifndef ACHATCOMMIT_H
#define ACHATCOMMIT_H

#include <QDialog>
#include <vector>
#include "mainwindow.h"
#include "annonce.h"
#include "dialogdetails.h"
#include "ui_achatcommit.h"


namespace Ui {
class AchatCommit;
}


class AchatCommit : public QDialog
{
    Q_OBJECT

public:
    explicit AchatCommit(DialogDetails *parent = 0, int _id = 0, std::vector<Annonce> *_ref_tab = nullptr);
    ~AchatCommit();
    DialogDetails *b_parent;
QString cheminstats ="/Users/Kodstok/build-TpQt-Desktop_Qt_5_6_0_clang_64bit-Profile/stats_conclus.xml";

private:

    Ui::AchatCommit *ui;
    int id;
    std::vector<Annonce> *tab_annonces;

private slots:
    void slotFinalConclure();

};

#endif // ACHATCOMMIT_H
