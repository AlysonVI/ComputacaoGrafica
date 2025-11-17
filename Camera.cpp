#include "Camera.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts),
    u(0,0,1), v(0,1,0), vpn(0,0,1),
    centerOfProjection(0,0,0) // rascunho
{
    this->angleRelativeToY = 0.0;

    FOV = 60; // Angulo de visao da camera na projecao paralela (rascunho)
}

void Camera::draw(QPainter &painter){}

// Alyson- ta com problemas, não ta concertando o up-vector de novo quando a camera é girada.
void Camera::rotateCamera(double Wupx, double Wupy) { // Os argumentos é o ponto onde a camera vai olhar
    Ponto avgPoint = getObjectAverage();
    //Ponto avgPoint = Ponto(0,0,0);
    angleRelativeToY = atan2(Wupx-avgPoint.getX(), Wupy-avgPoint.getY());
}

// funcao rascunho, ignore
void Camera::projectPerspective() {
    // cop to origin????

    // passo 2
    Ponto centroCamera = getObjectAverage();
    QVector<double> viewPlaneNormal; // VPN
}

// funcao rascunho, ignore
void Camera::getVPN() {

    Ponto p1(0,0,0);
    Ponto p2(0,0,0);
    Ponto p3(0,0,0);

    p1.transformPoint(-p1.getX(), -p1.getY(), -p1.getZ());
    p2.transformPoint(-p1.getX(), -p1.getY(), -p1.getZ());
    p3.transformPoint(-p1.getX(), -p1.getY(), -p1.getZ());
}
