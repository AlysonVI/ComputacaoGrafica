#ifndef PONTO_H
#define PONTO_H

#include <QPoint>
#include <QPainter>
#include <Matriz.h>

class Ponto : public Matriz {
public:


    Ponto(double x, double y);
    void draw(QPainter& painter) const;
    QPointF* convertToQPointF();

};

#endif
