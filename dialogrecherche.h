#ifndef DIALOGRECHERCHE_H
#define DIALOGRECHERCHE_H

#include <QDialog>

namespace Ui {
class DialogRecherche;
}

class DialogRecherche : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRecherche(QWidget *parent = 0);
    ~DialogRecherche();

private:
    Ui::DialogRecherche *ui;

private slots:
    void recherche();

};



#endif // DIALOGRECHERCHE_H
