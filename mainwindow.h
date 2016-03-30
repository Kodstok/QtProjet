#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>
#include <QMainWindow>
#include "possession.h"
#define MAX 6
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString types[MAX] = {"appartement","bureau","château","commerce","ferme","maison"};
    std::vector<possession> pos;
    void save();
private:
    Ui::MainWindow *ui;
private slots:
    void dialogAdd();
};

#endif // MAINWINDOW_H
