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


void Matriz::transladarPonto(double dX, double dY) {
    Matriz matrizTranslacao(3,3);

    matrizTranslacao[0][0] = 1; matrizTranslacao[0][1] = 0; matrizTranslacao[0][2] = dX;
    matrizTranslacao[1][0] = 0; matrizTranslacao[1][1] = 1; matrizTranslacao[1][2] = dY;
    matrizTranslacao[2][0] = 0; matrizTranslacao[2][1] = 0; matrizTranslacao[2][2] = 1;

    matrizTranslacao = matrizTranslacao * (*this);

    cout << matrizTranslacao[0][0] << " ";

    cout << matrizTranslacao[1][0] << " \n";
    (*this)[0][0]= matrizTranslacao[0][0];
    (*this)[1][0]= matrizTranslacao[1][0];
    (*this)[2][0]= matrizTranslacao[2][0];


}
