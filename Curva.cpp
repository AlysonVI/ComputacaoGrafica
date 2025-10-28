#include "Curva.h"

Curva::Curva(const QString& n, const Ponto& p0, const Ponto& p1, const Ponto& p2, int suavidade)
    : Drawable(n, ObjectType::Curva, {}) {

    casteljau(p0, p1, p2, suavidade);
}

void Curva::casteljau(const Ponto &p0, const Ponto &p1, const Ponto &p2, int n) {
    if(n <= 0) {
        points.append(p0);
        points.append(p2);
    }
    else {
        double p11x = (p0.getX() + p1.getX()) / 2;
        double p11y = (p0.getY() + p1.getY()) / 2;
        double p12x = (p1.getX() + p2.getX()) / 2;
        double p12y = (p1.getY() + p2.getY()) / 2;
        Ponto p11(p11x, p11y);
        Ponto p12(p12x, p12y);

        double p22x = (p11.getX() + p12.getX()) / 2;
        double p22y = (p11.getY() + p12.getY()) / 2;
        Ponto p22(p22x, p22y);

        casteljau(p0, p11, p22, n-1);
        casteljau(p22, p12, p2, n-1);
    }
}

void Curva::draw(QPainter& painter){

    int i = 0;
    for(i = 0; i < points.size(); i++){
        QPointF p12D(this->points[0].getX(), this->points[0].getY());
        QPointF p22D(this->points[i+1].getX(), this->points[i+1].getY());

        painter.drawLine((p12D), (p22D));
        i++;
    }
}
