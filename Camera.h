#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

class Camera : public Drawable{
private:
    Ponto centerOfProjection; // ponto que traça linhas imaginarias ate os pontos da window para criar o frustrum
    void getVPN(); // retorna View Plane Normal (vetor normal do plano de projeção)

    Ponto uVector; // vetorUp
    Ponto vVector; // u
    Ponto vpn; // Vetor normal ao plano de projeção
public:
    Ponto getVectorU();
    Ponto getVectorV();
    Ponto getVectorVpn();

    Camera(const QString& n, const QVector<Ponto>& pts);
    void draw(QPainter& painter) override;

    void rotateCamera(Ponto focusPoint); // ponto para onde a camera vai olhar
};

#endif // CAMERA_H
