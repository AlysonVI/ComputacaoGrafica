#include "Drawable.h"

Drawable::Drawable(const QString& n, ObjectType t, const QVector<Ponto>& pts)
    : nome(n), type(t), points(pts) {}

QVector<QPointF>* Drawable::getQPoints(){
    QVector<QPointF> *pointerToVector= new QVector<QPointF>;
    for(auto obj : points){
        pointerToVector->append(obj.convertToQPointF());
    }
    return pointerToVector;
}

void Drawable::transladar(double dX, double dY) {
    for(auto aux:points) {
        aux.transladarPonto(dX, dY);
    }
}
