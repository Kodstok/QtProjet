#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
private:
    Ui::MainWindow *ui;
private slots:
    void dialogAdd();
};

#endif // MAINWINDOW_H
