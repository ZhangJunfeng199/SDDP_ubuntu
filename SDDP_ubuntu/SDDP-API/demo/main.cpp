#include "mainwindow.h"
#include <QApplication>
//#include <boost/thread/thread.hpp>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("OpenIV Controller(V1.0)");
    w.show();

    return a.exec();
}
