#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

class Camera : public Drawable{
private:
    double FOV; // angulo de visualização da camera
    Ponto centerOfProjection; // ponto que traça linhas imaginarias ate os pontos da window para criar o frustrum
    void getVPN(); // retorna View Plane Normal (vetor normal do plano de projeção)

    const Ponto u; // vetorUp
    const Ponto v; // u
    const Ponto vpn; // Vetor normal ao plano de projeção
public:
    double angleRelativeToY;
    Camera(const QString& n, const QVector<Ponto>& pts);
    void draw(QPainter& painter) override;

    void rotateCamera(double Wupx, double Wupy);

    void projectPerspective();
};

#endif // CAMERA_H
