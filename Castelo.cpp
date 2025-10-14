#include "Castelo.h"

Castelo::Castelo(const Ponto& p)
    : Drawable("Castelo", ObjectType::Castelo,
               QVector<Ponto>{
                   // Aresta inferior e chão (Y=0, sem alteração)
                   {0 + p.getX(), 0 + p.getY()}, {25 + p.getX(), 0 + p.getY()}, {40 + p.getX(), 0 + p.getY()},
                   {60 + p.getX(), 0 + p.getY()}, {75 + p.getX(), 0 + p.getY()}, {100 + p.getX(), 0 + p.getY()},
                   // Topo da parede principal (Y agora é negativo)
                   {25 + p.getX(), -35 + p.getY()}, {75 + p.getX(), -35 + p.getY()},
                   // Porta Central (Y agora é negativo)
                   {40 + p.getX(), -20 + p.getY()}, {50 + p.getX(), -25 + p.getY()}, {60 + p.getX(), -20 + p.getY()},
                   // Torre esquerda (Y agora é negativo)
                   {0 + p.getX(), -50 + p.getY()}, {5 + p.getX(), -50 + p.getY()}, {5 + p.getX(), -45 + p.getY()},
                   {10 + p.getX(), -50 + p.getY()}, {10 + p.getX(), -45 + p.getY()}, {15 + p.getX(), -50 + p.getY()},
                   {15 + p.getX(), -45 + p.getY()}, {20 + p.getX(), -50 + p.getY()}, {20 + p.getX(), -45 + p.getY()},
                   {25 + p.getX(), -50 + p.getY()},
                   // Torre direita (Y agora é negativo)
                   {75 + p.getX(), -50 + p.getY()}, {80 + p.getX(), -50 + p.getY()}, {80 + p.getX(), -45 + p.getY()},
                   {85 + p.getX(), -50 + p.getY()}, {85 + p.getX(), -45 + p.getY()}, {90 + p.getX(), -50 + p.getY()},
                   {90 + p.getX(), -45 + p.getY()}, {95 + p.getX(), -50 + p.getY()}, {95 + p.getX(), -45 + p.getY()},
                   {100 + p.getX(), -50 + p.getY()},
                   // Bandeira (Y agora é negativo)
                   {50 + p.getX(), -35 + p.getY()}, {50 + p.getX(), -45 + p.getY()}, {50 + p.getX(), -50 + p.getY()},
                   {60 + p.getX(), -50 + p.getY()}, {60 + p.getX(), -45 + p.getY()}
               })

{
    this->dx = p.getX();
    this->dy = p.getY();
}

void Castelo::draw(QPainter& painter) {
    // Função lambda que retorna o ponto convertido para QPointF e já com o deslocamento, para agilizar
    auto getPoint = [&](double x, double y) {
        return *(Ponto(x + this->dx, y + this->dy).convertToQPointF());
    };

    // Desenha torre esquerda (com valores Y negativos)
    painter.drawLine(getPoint(0, 0), getPoint(0, -50));
    painter.drawLine(getPoint(0, -50), getPoint(5, -50));
    painter.drawLine(getPoint(5, -50), getPoint(5, -45));
    painter.drawLine(getPoint(5, -45), getPoint(10, -45));
    painter.drawLine(getPoint(10, -45), getPoint(10, -50));
    painter.drawLine(getPoint(10, -50), getPoint(15, -50));
    painter.drawLine(getPoint(15, -50), getPoint(15, -45));
    painter.drawLine(getPoint(15, -45), getPoint(20, -45));
    painter.drawLine(getPoint(20, -45), getPoint(20, -50));
    painter.drawLine(getPoint(20, -50), getPoint(25, -50));
    painter.drawLine(getPoint(25, -50), getPoint(25, 0));

    // Desenha torre direita (com valores Y negativos)
    painter.drawLine(getPoint(75, 0), getPoint(75, -50));
    painter.drawLine(getPoint(75, -50), getPoint(80, -50));
    painter.drawLine(getPoint(80, -50), getPoint(80, -45));
    painter.drawLine(getPoint(80, -45), getPoint(85, -45));
    painter.drawLine(getPoint(85, -45), getPoint(85, -50));
    painter.drawLine(getPoint(85, -50), getPoint(90, -50));
    painter.drawLine(getPoint(90, -50), getPoint(90, -45));
    painter.drawLine(getPoint(90, -45), getPoint(95, -45));
    painter.drawLine(getPoint(95, -45), getPoint(95, -50));
    painter.drawLine(getPoint(95, -50), getPoint(100, -50));
    painter.drawLine(getPoint(100, -50), getPoint(100, 0));

    // Desenha paredes e chão (com valores Y negativos)
    painter.drawLine(getPoint(0, 0), getPoint(25, 0));
    painter.drawLine(getPoint(25, 0), getPoint(75, 0));
    painter.drawLine(getPoint(75, 0), getPoint(100, 0));
    painter.drawLine(getPoint(25, -35), getPoint(75, -35));

    // Desenha porta (com valores Y negativos)
    painter.drawLine(getPoint(40, 0), getPoint(40, -20));
    painter.drawLine(getPoint(40, -20), getPoint(50, -25));
    painter.drawLine(getPoint(50, -25), getPoint(60, -20));
    painter.drawLine(getPoint(60, -20), getPoint(60, 0));

    // Desenha bandeira (com valores Y negativos)
    painter.drawLine(getPoint(50, -35), getPoint(50, -50));
    painter.drawLine(getPoint(50, -50), getPoint(60, -50));
    painter.drawLine(getPoint(60, -50), getPoint(60, -45));
    painter.drawLine(getPoint(60, -45), getPoint(50, -45));
}
