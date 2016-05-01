#ifndef OBJETA_H
#define OBJETA_H

#include <QDialog>
#include <vector>
#include "annonce.h"

class ObjetA : public QDialog
{
    Q_OBJECT

public:
    explicit ObjetA(QWidget *parent = 0, int id = 0, std::vector<Annonce> *_ref_tab = nullptr);
    ~ObjetA();
    int id_a;

private:
    std::vector<Annonce> *tab_annonces;


private slots:
    void viewAnnonce();

};



#endif // OBJETA_H
