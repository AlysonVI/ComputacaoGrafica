#include "Matriz.h"
#include <math.h>
#include <iostream>

using namespace std;

Matriz::Matriz(int l, int c) : vector<vector<double>>(l, vector<double>(c)) {}

Matriz Matriz::operator* (Matriz m){

    if((*this)[0].size() != m.size()) {
        cout << "Numero de colunas da primeira Matriz é diferente do numero de linhas da segunda Matriz";
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

    cout << transformMatrix[0][0] << " ";
    cout << transformMatrix[1][0] << " \n";
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

    cout << scaleMatrix[0][0] << " ";
    cout << scaleMatrix[1][0] << " \n";
    (*this)[0][0]= scaleMatrix[0][0];
    (*this)[1][0]= scaleMatrix[1][0];
    (*this)[2][0]= scaleMatrix[2][0];
}
