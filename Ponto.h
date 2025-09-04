#ifndef PONTO_H
#define PONTO_H

#include <QPoint>
#include <QPainter>

class Ponto {
    float coordenadas[3][1];
public:

    Ponto();
    Ponto(float x, float y);
    void draw(QPainter& painter) const;
    QPointF convertToQPointF();

};

#endif
