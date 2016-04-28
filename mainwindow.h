#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
#include "possession.h"
#include "annonce.h"
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
    std::vector<possession> pos;
    void save();


private:
    Ui::MainWindow *ui;

private slots:
    void dialogAdd();
    void dialogRech();
};

#endif // MAINWINDOW_H
