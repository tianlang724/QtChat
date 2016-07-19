#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = 0);
    void initWidgets();
    ~mainwindow();

private:
    Ui::mainwindow *ui;
};

#endif // MAINWINDOW_H
