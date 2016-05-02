#ifndef DIALOGDETAILS_H
#define DIALOGDETAILS_H

#include <QDialog>
#include <vector>
#include "mainwindow.h"
#include "annonce.h"
#include "ui_dialogdetails.h"
#include "ObjetA.h"


namespace Ui {
class DialogDetails;
}


class DialogDetails : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDetails(ObjetA *parent = 0, int _id = 0, std::vector<Annonce> *_ref_tab = nullptr);
    ~DialogDetails();
    ObjetA *d_parent;

private:
    Ui::DialogDetails *ui;
    int id;
    std::vector<Annonce> *tab_annonces;
    void actualiseImgs(QString file1, QString file2, QString file3, QString file4);

private slots:
    void slotConclure();

};

#endif // DialogDetails_H

