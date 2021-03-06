#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
#include <QScrollArea>
#include "possession.h"
#include "annonce.h"
#include "possession.h"

#define MAX 8
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::vector<Annonce> *tab_annonces;
    QScrollArea *scroll_annonces;
    void affiche_annonces(std::vector<Annonce> *tab_annonces);
    void reset_annonces();
    void refresh_annonces();

private:
    Ui::MainWindow *ui;
    QString chemin ="/Users/Kodstok/build-TpQt-Desktop_Qt_5_6_0_clang_64bit-Profile/annonces.xml";


private slots:
    void dialogAdd();
    void dialogRech();
    void quitMain();
    void slot_refresh();

};

#endif // MAINWINDOW_H
