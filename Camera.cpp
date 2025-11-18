#include "Camera.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts),
    u(1,0,0), v(0,1,0), vpn(0,0,1),
    centerOfProjection(0,0,0) // rascunho
{
    this->angleRelativeToY = 0.0;

    FOV = 60; // Angulo de visao da camera na projecao paralela (rascunho)
}

void Camera::draw(QPainter &painter){}

// Alyson- ta com problemas, não ta concertando o up-vector de novo quando a camera é girada.
void Camera::rotateCamera(double Wupx, double Wupy) { // Os argumentos é o ponto onde a camera vai olhar
    Ponto avgPoint = getObjectAverage();
    angleRelativeToY = atan2(Wupx-avgPoint.getX(), Wupy-avgPoint.getY());
}

// funcao rascunho, ignore
void Camera::projectPerspective() {
    // cop to origin????

    // passo 2
    Ponto centroCamera = getObjectAverage();
    QVector<double> viewPlaneNormal; // VPN
}

void Camera::setVectorU(Ponto u) {
    this->u = u;
}

void Camera::setVectorV(Ponto v) {
    this->v = v;
}

void Camera::setVectorVpn(Ponto vpn) {
    this->vpn = vpn;
}
