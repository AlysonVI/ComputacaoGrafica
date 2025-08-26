#include "mainwindowalyson.h"
#include "objeto.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Objeto objeto = new Objeto((1,2),(3,4));

    objeto.revelaPontos();
    Ponto.x = 2;
    List list = new List();
    QApplication a(argc, argv);
    MainWindowAlyson w;
    w.show();
    return a.exec();
}
