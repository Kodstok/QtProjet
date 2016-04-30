#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
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
    //std::vector<possession> pos;
    void save();



    std::vector<Annonce> *tab_annonces;

    //possession *pos;
    std::vector<Annonce> tab_annonces_bis;
    std::vector<Annonce> &ref_tab = tab_annonces_bis;


private:
    Ui::MainWindow *ui;

private slots:
    void dialogAdd();
    void dialogRech();
    void quitMain();
};

#endif // MAINWINDOW_H
