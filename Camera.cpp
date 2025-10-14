#include "Camera.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts)
{
    this->angleRelativeToX= 0.0;
}

void Camera::draw(QPainter &painter){

}

void Camera::rotateCamera(double Wupx, double Wupy){//Os argumentos é o ponto onde a camera vai olhar
    angleRelativeToX= atan2(Wupx-(*getObjectAverage())[0], Wupy-(*getObjectAverage())[1]);
}
double Camera::getVariable(){
    return angleRelativeToX;
}
