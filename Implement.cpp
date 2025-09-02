#include "Implement.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>

MyCanvas::MyCanvas() {
    display.add(new Linha("baixo", QPointF(0,0), QPointF(100,0)));
    display.add(new Linha("extrema direita",  QPointF(100,0), QPointF(100,100)));
    display.add(new Linha("cima",    QPointF(100,100), QPointF(0,100)));
    display.add(new Linha("esquerda",   QPointF(0,100), QPointF(0,0)));

    display.add(new Polygon("rect", QVector<QPointF>{
        {120, 0}, {220, 0}, {220, 100}, {120, 100}
    }));
    display.add(new Ponto("Pontao", QPointF(50, 50)));
    display.printAll();
}

void MyCanvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    painter.setWindow(0, 0, 300, 200);
    painter.setViewport(0, 0, width(), height());

    display.drawAll(painter);
}
