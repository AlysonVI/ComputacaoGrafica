#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

class Camera : public Drawable{
public:
    Camera(const QString& n, const QVector<Ponto>& pts);
    void draw(QPainter& painter) override;
    void generateSCNDescription();

};

#endif // CAMERA_H
