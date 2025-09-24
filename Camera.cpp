#include "Camera.h"

Camera::Camera(const QString& n, const QVector<Ponto>& pts)
    : Drawable(n, ObjectType::Camera, pts)
{}

void Camera::draw(QPainter &painter){
    painter.drawPolygon(*getQPoints());
}

void Camera::generateSCNDescription(){

}
