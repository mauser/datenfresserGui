#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);
    MainWindow w;
    w.setWindowTitle("datenfresserGui");
    w.show();
    //w.hide();
    return a.exec();
}
