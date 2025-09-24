#ifndef PONTO_H
#define PONTO_H

#include <QPoint>
#include <QPainter>
#include <Matriz.h>

class Ponto : public Matriz {
public:
    double xSCN;
    double ySCN;
    double zSCN;

    Ponto(double x, double y);
    void draw(QPainter& painter) const;
    QPointF* convertToQPointF();

};

#endif
