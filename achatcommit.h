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


private:

    Ui::AchatCommit *ui;
    int id;
    std::vector<Annonce> *tab_annonces;

private slots:
    void slotFinalConclure();

};

#endif // ACHATCOMMIT_H
