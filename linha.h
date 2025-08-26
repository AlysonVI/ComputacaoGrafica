#ifndef LINHA_H
#define LINHA_H
#include <ponto.h>

class Linha
{
public:
    Ponto a, b;

    Linha();
    Linha(Ponto a, Ponto b);
    ~Linha();

};

#endif // LINHA_H
