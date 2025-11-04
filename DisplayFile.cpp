#include "DisplayFile.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QVector>

DisplayFile::~DisplayFile(){
    for(auto& obj : objects) delete obj;
}

void DisplayFile::add(Drawable* obj) {
    objects.append(obj);
}

void DisplayFile::drawAll(QPainter& painter) const {
    for(auto obj : objects)
        obj->draw(painter);
}

void DisplayFile::printAll() const{
    for(auto obj : objects)
        std::cout << "Objeto " << obj->getNome().toStdString() << "\n";
}
Drawable* DisplayFile::getObject(int n){
    return objects[n];
}

void DisplayFile::triggerTranslate(){
    Ponto centroWindow = getObject(0)->getObjectAverage();
    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->transformObject(-centroWindow.getX(), -centroWindow.getY(), -centroWindow.getZ());
    }
}

/*void DisplayFile::triggerRotate(double theta){
    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->rotateObject(-theta);
    }
}*/

void DisplayFile::applyGlobalTransform(double theta) {
    Matriz globalMatrix = getWorldToCameraMatrix(theta);

    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->applyMatrix(globalMatrix);
    }
}
Matriz DisplayFile::getWorldToCameraMatrix(double theta) {//matriz global para fazer translaçãp para centro e rotação baseado no angulo calculado antes (relativeToX)
    Ponto centroCamera = getObject(0)->getObjectAverage();
    double cx = centroCamera.getX();
    double cy = centroCamera.getY();
    double cz = centroCamera.getZ();

    Matriz T(3,3), R(3,3);
    T = T.getTransformMatrix(-cx, -cy, -cz);
    R = R.getRotateMatrixZ(-theta);

    Matriz globalMatrix = R * T;
    return globalMatrix;
}

void DisplayFile::triggerNormalize(double Wxmax, double Wxmin, double Wymax, double Wymin) {


    for (auto& obj : objects) {
        if(obj->getType() == ObjectType::Camera) continue;
        obj->normalizeObject(Wxmin, Wxmax, Wymin, Wymax);
    }
}

void DisplayFile::triggerViewport(double Vxmax, double Vxmin, double Vymax, double Vymin) {


    for (auto& obj : objects) {
        if(obj->getType() == ObjectType::Camera) continue;
        obj->viewportObject(Vxmin, Vxmax, Vymin, Vymax);
    }
}
