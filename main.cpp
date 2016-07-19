#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;
    w.show();
    mainwindow myMainWindow;
    w.mw = &myMainWindow;
    return a.exec();
}
