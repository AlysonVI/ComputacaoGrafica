#include "mainwindow.h"
#include "Implement.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyCanvas canvas;
    MainWindow window;
    window.show();
    //canvas.show();
    return a.exec();
}
