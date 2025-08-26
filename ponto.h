#ifndef PONTO_H
#define PONTO_H


class Ponto
{
public:
    float x;
    float y;

    Ponto();
    Ponto(float x, float y);
    ~Ponto();

    void mostraPonto();
};

#endif // PONTO_H
