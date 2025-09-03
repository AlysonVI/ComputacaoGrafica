#ifndef PONTO_H
#define PONTO_H
#include <vector>

using namespace std;

class Ponto
{
public:

    //O vetor de vetores de floats representa as coordenadas (x,y) escritas
    //em matrizes M2x1; 2 linhas ; 1 coluna
    //vector<vector<float>> coordenadas;
    float coordenadas[2][1];




    Ponto();
    Ponto(float x, float y);
    ~Ponto();

    void mostraPonto();
};

#endif // PONTO_H
