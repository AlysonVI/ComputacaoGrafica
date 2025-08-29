<<<<<<< HEAD
#include <ponto.h>
#include <objeto.h>
#include <mainwindowalyson.h>
#include <QApplication>
#include <iostream>

using namespace std;


int main(int argc, char *argv[])
{
=======
#include "mainwindowalyson.h"
#include "objeto.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Objeto objeto = new Objeto((1,2),(3,4));

    objeto.revelaPontos();
    Ponto.x = 2;
    List list = new List();
>>>>>>> pontos_linhas
    QApplication a(argc, argv);

    Ponto p1(1,2);
    Ponto p2(3,4);
    Ponto p3(10,2);
    Ponto p4(3,43);

    //p1.mostraPonto();

    Linha l1(p1,p2);
    Linha l2(p3,p4);

    Objeto o1("Reta");

    o1.adicionaLinha(l1);
    o1.adicionaLinha(l2);


    o1.mostraLinhas();

    MainWindowAlyson w;
    w.show();

    return a.exec();
}
