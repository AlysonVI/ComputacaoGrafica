#include "Matriz.h"
#include <math.h>
#include <iostream>

using namespace std;

Matriz::Matriz(int l, int c) : vector<vector<double>>(l, vector<double>(c)) {}

Matriz Matriz::operator* (Matriz m){

    if((*this)[0].size() != m.size()) {

        cout << "Numero de colunas da primeira matriz é diferente do numero de linhas da segunda matriz";

        return m;
    }

    Matriz produto(this->size(), m[0].size());
    for (size_t i = 0; i < this->size(); i++) {
        for (size_t j = 0; j < m[0].size(); j++) {
            double soma = 0;
            for (size_t h = 0; h < (*this)[0].size(); h++)
                soma += (*this)[i][h] * m[h][j];
            produto[i][j] = soma;
        }
    }

    return produto; //retorna cópia, variavel criada é excluida ao fim da execução.
}

Matriz Matriz::operator + (Matriz m){
    if (this->size() != m.size() || (*this)[0].size() != m[0].size()) {
        cout << "Matrizes têm tamanhos diferentes\n";
        return Matriz(0,0);
    }

    Matriz soma(this->size(), (*this)[0].size());

    for (size_t i = 0; i < this->size(); i++) {
        for (size_t j = 0; j < (*this)[0].size(); j++) {
            soma[i][j] = (*this)[i][j] + m[i][j];
        }
    }
    return soma;
}

void Matriz::transformPoint(double dX, double dY) {
    Matriz transformMatrix(3,3);

    transformMatrix[0][0] = 1; transformMatrix[0][1] = 0; transformMatrix[0][2] = dX;
    transformMatrix[1][0] = 0; transformMatrix[1][1] = 1; transformMatrix[1][2] = dY;
    transformMatrix[2][0] = 0; transformMatrix[2][1] = 0; transformMatrix[2][2] = 1;

    transformMatrix = transformMatrix * (*this);


    (*this)[0][0]= transformMatrix[0][0];
    (*this)[1][0]= transformMatrix[1][0];
    (*this)[2][0]= transformMatrix[2][0];
}


void Matriz::scalePoint(double sX, double sY) {
    Matriz scaleMatrix(3,3);

    scaleMatrix[0][0] = sX; scaleMatrix[0][1] = 0; scaleMatrix[0][2] = 0;
    scaleMatrix[1][0] = 0; scaleMatrix[1][1] = sY; scaleMatrix[1][2] = 0;
    scaleMatrix[2][0] = 0; scaleMatrix[2][1] = 0; scaleMatrix[2][2] = 1;

    scaleMatrix = scaleMatrix * (*this);

    (*this)[0][0]= scaleMatrix[0][0];
    (*this)[1][0]= scaleMatrix[1][0];
    (*this)[2][0]= scaleMatrix[2][0];
}


void Matriz::rotatePoint(double ang) {
    Matriz rotateMatrix(3,3);

    rotateMatrix[0][0] = cos(ang); rotateMatrix[0][1] = -sin(ang); rotateMatrix[0][2] = 0;
    rotateMatrix[1][0] = sin(ang); rotateMatrix[1][1] = cos(ang); rotateMatrix[1][2] = 0;
    rotateMatrix[2][0] = 0; rotateMatrix[2][1] = 0; rotateMatrix[2][2] = 1;

    rotateMatrix= rotateMatrix * (*this);

    (*this)[0][0]= rotateMatrix[0][0];
    (*this)[1][0]= rotateMatrix[1][0];
    (*this)[2][0]= rotateMatrix[2][0];
}
void Matriz::toSCN(double Wxmin, double Wxmax, double Wymin, double Wymax, bool useMinusOneToOne) {

    transformPoint(-Wxmin, -Wymin);

    double sx = 1.0 / (Wxmax - Wxmin);
    double sy = 1.0 / (Wymax - Wymin);
    scalePoint(sx, sy);

    if (useMinusOneToOne) {
        transformPoint(-0.5, -0.5);
        scalePoint(2, 2);
    }

    xSCN = (*this)[0][0];
    ySCN = (*this)[1][0];
    zSCN = (*this)[2][0];
}

void Matriz::toViewport(double Vxmin, double Vxmax, double Vymin, double Vymax, bool scnMinusOneToOne) {
    double x = (*this)[0][0];
    double y = (*this)[1][0];

    if(scnMinusOneToOne){
        x = (x + 1.0) / 2.0;
        y = (y + 1.0) / 2.0;
    }

    double xv = Vxmin + x * (Vxmax - Vxmin);
    double yv = Vymin + (1 - y) * (Vymax - Vymin);
    (*this)[0][0] = xv;
    (*this)[1][0] = yv;
}

Matriz Matriz::getTransformMatrix(double dX, double dY) {
    Matriz T(3,3);
    T[0][0] = 1; T[0][1] = 0; T[0][2] = dX;
    T[1][0] = 0; T[1][1] = 1; T[1][2] = dY;
    T[2][0] = 0; T[2][1] = 0; T[2][2] = 1;
    return T;
}

Matriz Matriz::getRotateMatrix(double ang) {
    Matriz R(3,3);
    R[0][0] = cos(ang); R[0][1] = -sin(ang); R[0][2] = 0;
    R[1][0] = sin(ang); R[1][1] = cos(ang);  R[1][2] = 0;
    R[2][0] = 0;        R[2][1] = 0;         R[2][2] = 1;
    return R;
}
