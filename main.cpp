#include "mainwindowalyson.h"

#include <QApplication>
class Ponto{
    float x;
    float y;

    int cor;

    ponto(){}
    ~ponto(){}
};

int main(int argc, char *argv[])
{
    Ponto ponto = new Ponto();
    Ponto.x = 2;
    List list = new List();
    QApplication a(argc, argv);
    MainWindowAlyson w;
    w.show();
    return a.exec();
}
