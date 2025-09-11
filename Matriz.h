#ifndef MATRIZ_H
#define MATRIZ_H
#include <vector>
using namespace std;

class Matriz : public vector<vector<double>>
{
public:
    Matriz(int l, int c); //Construtor da matriz, l para Linha e C para colunas
    Matriz operator * (Matriz m); //operador de multiplicação de matriz
    Matriz operator + (Matriz m); //operador de soma de matriz
    void transladarPonto(double dX, double dY);
    void redimensionarPonto(double sX, double sY);
    void rotacionarPonto(double ang);
};

#endif
