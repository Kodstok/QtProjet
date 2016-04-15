#ifndef DIALOGNEWB_H
#define DIALOGNEWB_H

#include <QDialog>
#include "dialognewA.h"

namespace Ui {
class DialogNewB;
}

class DialogNewB : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewB(QWidget *parent = 0, QString _num = "", QString _code = "", QString _ville = "", QString _type = "", int _piece = 0, double _surfaceT = 0.0, double _surfaceH = 0.0, QString _nom = "", QString _prenom = "", QString _mail = "", QString _tel = "", QString _typeV = "", double _prix = 0.0, QString _titre = "", QString _descr = "", QString _image1 = "", QString _image2 = "", QString _image3 = "", QString _image4 = "");
    ~DialogNewB();

private:
    Ui::DialogNewB *ui;


    QString num;
    QString code;
    QString ville;
    QString type;
    int piece;
    double surfaceT;
    double surfaceH;
    QString nom;
    QString prenom;
    QString mail;
    QString tel;
    QString typeV;
    double prix;
    QString titre;
    QString descr;
    QString image1;
    QString image2;
    QString image3;
    QString image4;

    void actualiseImgs(QString file1, QString file2, QString file3, QString file4);

private slots:
    void addImg1();
    void addImg2();
    void addImg3();
    void addImg4();
    void add();
    void previous();


};

#endif // DialogNewB_H
