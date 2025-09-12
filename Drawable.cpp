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
    vector<double>* avgPoint= getObjectAverage();
    this->goToOrigin(avgPoint);

    for(auto& aux: points) {
        aux.scalePoint(sX, sY);
    }
    this->returnFromOrigin(avgPoint);
}

void Drawable::rotateObject(double ang) {
    vector<double>* avgPoint= getObjectAverage();
    this->goToOrigin(avgPoint);

    for(auto& aux: points) {
        aux.rotatePoint(ang);
    }
    this->returnFromOrigin(avgPoint);
}

vector<double>* Drawable::getObjectAverage() {
    double somaX= 0, somaY= 0;

    for(int i=0; i<points.size(); i++) {
        somaX += (points[i])[0][0];
        somaY += (points[i])[1][0];
    }
    cout << "\n\n\nMedia: " << somaX/points.size() << " , " << somaY/points.size() << "\n\n\n";
    vector<double>* referencePoint= new vector<double>(2, 0);
    (*referencePoint)[0]= somaX/points.size();
    (*referencePoint)[1]= somaY/points.size();
    return referencePoint;
}

// transporta matriz pro 0,0
void Drawable::goToOrigin(vector<double> *avgPoint) {

    double dX = (*avgPoint)[0];
    double dY = (*avgPoint)[1];
    transformObject(-dX, -dY);
}

// tras objeto de volta do 0,0
void Drawable::returnFromOrigin(vector<double>* avgPoint) {
    double dX = (*avgPoint)[0];
    double dY = (*avgPoint)[1];

    transformObject(dX, dY);
}
