#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

class Camera : public Drawable{
private:
    Ponto vpn; // Vetor normal ao plano de projeção
    void getVPN(); // retorna View Plane Normal (vetor normal do plano de projeção)

public:
    const double distance = 400; // define o "fov" da camera

    Ponto getVectorVpn();
    void setVectorVpn(Ponto newVpn);

    Camera(const QString& n, const QVector<Ponto>& pts);
    void draw(QPainter& painter) override;

    void rotateCamera(Ponto focusPoint); // ponto para onde a camera vai olhar
};

#endif // CAMERA_H
