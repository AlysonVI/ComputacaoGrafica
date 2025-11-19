#include "Camera.h"
#include "Ponto.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts),
    uVector(1,0,0), vVector(0,1,0), vpn(0,0,1),
    centerOfProjection(0,0,0) // rascunho
{}

void Camera::draw(QPainter &painter){}

// Alyson- ta com problemas, não ta concertando o up-vector de novo quando a camera é girada.
void Camera::rotateCamera(Ponto focusPoint) { // Os argumentos é o ponto onde a camera vai olhar

    // angulo[0] = angulo relativo a x, angulo[1] = angulo relativo a y
    QVector<double> angulo = Ponto::getAnglesfromVectors(vpn, focusPoint);

    uVector.rotatePointX(angulo[0]);
    uVector.rotatePointY(angulo[1]);

    vVector.rotatePointX(angulo[0]);
    vVector.rotatePointY(angulo[1]);

    vpn.rotatePointX(angulo[0]);
    vpn.rotatePointY(angulo[1]);
}

Ponto Camera::getVectorU() {
    return this->uVector;
}

Ponto Camera::getVectorV() {
    return this->vVector;
}

Ponto Camera::getVectorVpn() {
    return this->vpn;
}
