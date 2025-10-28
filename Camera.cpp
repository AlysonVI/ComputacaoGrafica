#include "Camera.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts)
{
    this->angleRelativeToX= 0.0;
}

void Camera::draw(QPainter &painter){}

void Camera::rotateCamera(double Wupx, double Wupy){//Os argumentos é o ponto onde a camera vai olhar
    Ponto avgPoint = getObjectAverage();
    angleRelativeToX= atan2(Wupx-avgPoint.getX(), Wupy-avgPoint.getY());
}
