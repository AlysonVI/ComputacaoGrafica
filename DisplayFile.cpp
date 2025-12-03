#include "DisplayFile.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QVector>
#include "Ponto.h"

DisplayFile::~DisplayFile() {
    for(auto& obj : objects) delete obj;
}

void DisplayFile::add(Drawable* obj) {
    objects.append(obj);
}

void DisplayFile::drawAll(QPainter& painter) const {
    for(auto obj : objects)
        obj->draw(painter);
}

void DisplayFile::printAll() const {
    for(auto obj : objects)
        std::cout << "Objeto " << obj->getNome().toStdString() << "\n";
}

Drawable* DisplayFile::getObject(int n) {
    return objects[n];
}

void DisplayFile::triggerTranslate() {
    Ponto centroWindow = getObject(0)->getObjectAverage();

    for(auto& obj : objects) {
        obj->transformObject(-centroWindow.getX(), -centroWindow.getY(), -centroWindow.getZ());
    }
}

void DisplayFile::applyGlobalTransform(Camera* pToCamera) {
    Matriz globalMatrix = getWorldToCameraMatrix(pToCamera);

    for(auto& obj : objects){
        obj->applyViewMatrix(globalMatrix);
    }
}

Matriz DisplayFile::getWorldToCameraMatrix(Camera* pToCamera) {  // matriz global para fazer translaçãp para centro e rotação baseado no angulo calculado antes (relativeToX)
    Ponto centroCamera = pToCamera->getObjectAverage();

    Matriz T(4,4), R(4,4);
    T = T.getTransformMatrix(-centroCamera.getX(), -centroCamera.getY(), -centroCamera.getZ());

    QVector<double> angulo = Ponto::getAnglesfromVectors(pToCamera->getVectorVpn(), Ponto(0,0,1));
    R = R.getRotateMatrixX(-angulo[0]);
    R = R * R.getRotateMatrixY(-angulo[1]);

    Matriz globalMatrix = R * T;
    return globalMatrix;
}

void DisplayFile::triggerPerspective(double d) {
    for (auto& obj : objects) {
        if(obj->getType() == ObjectType::Camera) continue;
        obj->projectObject(d);
    }
}

void DisplayFile::triggerNormalize(double Wxmax, double Wxmin, double Wymax, double Wymin) {
    for (auto& obj : objects) {
        obj->normalizeObject(Wxmin, Wxmax, Wymin, Wymax);
    }
}

// Faz o clip de cada objeto do display file no eixo Z, e salva seus novos pontos clipados em normPoints de cada objeto
void DisplayFile::triggerZClipping() {
    for (auto& obj : objects) {
        obj->clipObjectZ();
    }
}

// Faz o clip de cada objeto do display file nos eixos X e Y, e salva seus novos pontos clipados em normPoints de cada objeto
void DisplayFile::triggerXYClipping(double Wxmax, double Wxmin, double Wymax, double Wymin) {
    for (auto& obj : objects) {
        obj->clipObjectXY(Wxmax, Wxmin, Wymax, Wymin);
    }
}

void DisplayFile::triggerViewport(double Vxmax, double Vxmin, double Vymax, double Vymin) {
    for (auto& obj : objects) {
        obj->viewportObject(Vxmin, Vxmax, Vymin, Vymax);
    }
}


