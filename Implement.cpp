#include "Implement.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>

MyCanvas::MyCanvas() {
    //Quadrado definido pelas linhas
    display.add(new Linha("baixo", Ponto(0,0), Ponto(100,0)));
    display.add(new Linha("extrema direita",  Ponto(100,0), Ponto(100,100)));
    display.add(new Linha("cima",    Ponto(100,100), Ponto(0,100)));
    display.add(new Linha("esquerda",   Ponto(0,100), Ponto(0,0)));

    display.add(new Polygon("rect", QVector<Ponto>{
        {120, 0}, {220, 0}, {220, 100}, {120, 100}
    }));

    display.printAll();
}

void MyCanvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    painter.setWindow(0, 0, 300, 200);
    painter.setViewport(0, 0, width(), height());

    display.drawAll(painter);
}
