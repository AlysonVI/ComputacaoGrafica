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
{}

void Castelo::draw(QPainter& painter) {
    QVector<QPointF> pontos = *(this->getQPoints()); // Esses pontos ja incluem o deslocamento

    // ==== Desenha torre esquerda ====
    // Linha vertical da parede da torre
    painter.drawLine(pontos[0], pontos[11]);
    // Topo da Torre
    painter.drawLine(pontos[11], pontos[12]);
    painter.drawLine(pontos[12], pontos[13]);
    painter.drawLine(pontos[13], pontos[15]);
    painter.drawLine(pontos[15], pontos[14]);
    painter.drawLine(pontos[14], pontos[16]);
    painter.drawLine(pontos[16], pontos[17]);
    painter.drawLine(pontos[17], pontos[19]);
    painter.drawLine(pontos[19], pontos[18]);
    painter.drawLine(pontos[18], pontos[20]);
    // Linha vertical até o chão
    painter.drawLine(pontos[20], pontos[1]);

    // ==== Desenha torre direita ====
    // Linha vertical da parede da torre
    painter.drawLine(pontos[4], pontos[21]);
    // Topo da torre
    painter.drawLine(pontos[21], pontos[22]);
    painter.drawLine(pontos[22], pontos[23]);
    painter.drawLine(pontos[23], pontos[25]);
    painter.drawLine(pontos[25], pontos[24]);
    painter.drawLine(pontos[24], pontos[26]);
    painter.drawLine(pontos[26], pontos[27]);
    painter.drawLine(pontos[27], pontos[29]);
    painter.drawLine(pontos[29], pontos[28]);
    painter.drawLine(pontos[28], pontos[30]);
    // Linha vertical até o chão
    painter.drawLine(pontos[30], pontos[5]);

    // ==== Desenha paredes e chão
    // Linha do chão
    painter.drawLine(pontos[0], pontos[5]);
    // Topo da parece principal
    painter.drawLine(pontos[6], pontos[7]);

    // ==== Desenha porta ====
    painter.drawLine(pontos[2], pontos[8]);
    painter.drawLine(pontos[8], pontos[9]);
    painter.drawLine(pontos[9], pontos[10]);
    painter.drawLine(pontos[10], pontos[3]);

    // ==== Desenha bandeira ====
    // Mastro
    painter.drawLine(pontos[31], pontos[33]);
    // Tecido da bandeira
    painter.drawLine(pontos[33], pontos[34]);
    painter.drawLine(pontos[34], pontos[35]);
    painter.drawLine(pontos[35], pontos[32]);
}
