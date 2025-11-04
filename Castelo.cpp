#include "Castelo.h"

Castelo::Castelo(const Ponto& p)
    : Drawable("Castelo", ObjectType::Castelo, {}) {

    QVector<Ponto> pontos = {
        //Torre Esquerda
        {0, 0}, {0, -50},
        {0, -50}, {5, -50},
        {5, -50}, {5, -45},
        {5, -45}, {10, -45},
        {10, -45}, {10, -50},
        {10, -50}, {15, -50},
        {15, -50}, {15, -45},
        {15, -45}, {20, -45},
        {20, -45}, {20, -50},
        {20, -50}, {25, -50},
        {25, -50}, {25, 0},

        //Torre Direita
        {75, 0}, {75, -50},
        {75, -50}, {80, -50},
        {80, -50}, {80, -45},
        {80, -45}, {85, -45},
        {85, -45}, {85, -50},
        {85, -50}, {90, -50},
        {90, -50}, {90, -45},
        {90, -45}, {95, -45},
        {95, -45}, {95, -50},
        {95, -50}, {100, -50},
        {100, -50}, {100, 0},

        //Paredes e Chão
        {0, 0}, {100, 0}, // Chão
        {25, -35}, {75, -35}, // Topo da parede principal

        //Porta
        {40, 0}, {40, -20},
        {40, -20}, {50, -25},
        {50, -25}, {60, -20},
        {60, -20}, {60, 0},

        //Bandeira
        {50, -35}, {50, -50},
        {50, -50}, {60, -50},
        {60, -50}, {60, -45},
        {60, -45}, {50, -45}
    };

    for(auto& ponto : pontos)
        points.append(ponto);

    this->transformObject(p.getX(), p.getY(), p.getZ());
}

void Castelo::draw(QPainter& painter) { // faz projecao ortogonal

    int i = 0;
    for(i = 0; i < (normPoints.size() - 1); i++) {
        QPointF p12D(normPoints[i].getX(), normPoints[i].getY());
        QPointF p22D(normPoints[i+1].getX(), normPoints[i+1].getY());

        painter.drawLine((p12D), (p22D));
        i++;
    }
}
