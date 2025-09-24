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
    void transformPoint(double dX, double dY);
    void scalePoint(double sX, double sY);
    void rotatePoint(double ang);
    Matriz getTransformMatrix(double dX, double dY);
    Matriz getScaleMatrix(double sX, double sY);
    Matriz getRotateMatrix(double ang);
};

#endif
