#include "DisplayFile.h"

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
    vector<double>* centroWindow= getObject(0)->getObjectAverage();
    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->transformObject(-(*centroWindow)[0], -(*centroWindow)[1]);
    }
}

void DisplayFile::triggerRotate(){ //inutil por enquanto
    double theta= getObject(0)->getVariable();
    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->rotateObject(-theta);
    }
}

void DisplayFile::applyGlobalTransform() {
    Matriz globalMatrix = getWorldToCameraMatrix();

    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->applyMatrix(globalMatrix);
    }
}
Matriz DisplayFile::getWorldToCameraMatrix() {//matriz global para fazer translaçãp para centro e rotação baseado no angulo calculado antes (relativeToX)
    vector<double>* centroCamera = getObject(0)->getObjectAverage();
    double cx = (*centroCamera)[0];
    double cy = (*centroCamera)[1];
    double theta = getObject(0)->getVariable();

    Matriz T(3,3), R(3,3);
    T = T.getTransformMatrix(-cx, -cy);
    R = R.getRotateMatrix(-theta);

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
