#include <ponto.h>
#include <mainwindowalyson.h>
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ponto p1(1,2);

    p1.mostraPonto();

    MainWindowAlyson w;
    w.show();

    return a.exec();
}
