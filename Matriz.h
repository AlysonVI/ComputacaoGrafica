#ifndef MATRIZ_H
#define MATRIZ_H
#include <vector>
using namespace std;

class Matriz : public vector<vector<double>>
{
public:
    double xSCN; //normalizada
    double ySCN;
    double zSCN;

    Matriz(int l, int c); //Construtor da matriz, l para Linha e C para colunas
    Matriz operator * (Matriz m); //operador de multiplicação de matriz
    Matriz operator + (Matriz m); //operador de soma de matriz

    void transformPoint(double dX, double dY, double dZ);
    void scalePoint(double sX, double sY, double sZ);
    void rotatePointX(double ang);
    void rotatePointY(double ang);
    void rotatePointZ(double ang);

    Matriz getTransformMatrix(double dX, double dY, double dZ);
    Matriz getScaleMatrix(double sX, double sY, double sZ);
    Matriz getRotateMatrixX(double ang);
    Matriz getRotateMatrixY(double ang);
    Matriz getRotateMatrixZ(double ang);

    void toViewport(double Vxmin, double Vxmax, double Vymin, double Vymax, bool scnMinusOneToOne);
    void toSCN(double Wxmin, double Wxmax, double Wymin, double Wymax, bool useMinusOneToOne);
};

#endif
