#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>

namespace Ui {
class DialogNew;
}

class DialogNew : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNew(QWidget *parent = 0);
    ~DialogNew();

private:
    Ui::DialogNew *ui;
private slots:
    void addImg();
    void add();
};

#endif // DIALOGNEW_H
