#include "Camera.h"
#include "Ponto.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts), vpn(0,0,1)
{}

void Camera::draw(QPainter &painter){}

void Camera::rotateCamera(Ponto focusPoint) { // Os argumentos é o ponto onde a camera vai olhar

    // angulo[0] = angulo relativo a x, angulo[1] = angulo relativo a y
    QVector<double> angulo = Ponto::getAnglesfromVectors(vpn, focusPoint);

    vpn.rotatePointX(angulo[0]);
    vpn.rotatePointY(angulo[1]);
}

Ponto Camera::getVectorVpn() {
    return this->vpn;
}

void Camera::setVectorVpn(Ponto newVpn) {
    this->vpn = newVpn;
}
