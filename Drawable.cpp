#include "Drawable.h"
#include <iostream>
using namespace std;

Drawable::Drawable(const QString& n, ObjectType t, const QVector<Ponto>& pts)
    : nome(n), type(t), points(pts) {}

QVector<QPointF>* Drawable::getQPoints(){
    QVector<QPointF> *pointerToVector= new QVector<QPointF>;
    for(auto obj : points){
        pointerToVector->append(*(obj.convertToQPointF()));
    }
    return pointerToVector;
}

void Drawable::transformObject(double dX, double dY) {
    for(auto& aux: points) {
        aux.transformPoint(dX, dY);
    }
}

void Drawable::scaleObject(double sX, double sY) {
    this->goToOrigin();
    for(auto& aux: points) {
        aux.scalePoint(sX, sY);
    }
    this->returnFromOrigin();
}

vector<double>* Drawable::getObjectAverage() {
    double somaX, somaY;

    for(int i=0; i<(this->points.size()); i++) {
        somaX += (points[i])[0][0];
        somaY += (points[i])[1][0];
    }

    return new vector<double>(somaX/points.size(), somaY/points.size());
}

// transporta matriz pro 0,0
void Drawable::goToOrigin() {
    vector<double>* avgPoint = getObjectAverage();
    double dX = (*avgPoint)[0];
    double dY = (*avgPoint)[1];
    cout << "\n\n\nMedia: " << dX << " , " << dY << "\n\n\n";
    transformObject(-dX, -dY);
}

// tras objeto de volta do 0,0
void Drawable::returnFromOrigin() {
    vector<double>* avgPoint = getObjectAverage();
    double dX = (*avgPoint)[0];
    double dY = (*avgPoint)[1];
    transformObject(dX, dY);
}
