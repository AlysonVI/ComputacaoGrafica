#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

class Camera : public Drawable{
public:
    double angleRelativeToX;
    Camera(const QString& n, const QVector<Ponto>& pts);
    void draw(QPainter& painter) override;
    double getVariable() override;

    void rotateCamera(double Wupx, double Wupy);
};

#endif // CAMERA_H
