#include "Matriz.h"
#include <iostream>

using namespace std;

Matriz::Matriz(int l, int c) : vector<vector<double>>(l, vector<double>(c)) {}

Matriz Matriz::operator* (Matriz m){

    if(this->size() != m[0].size()) {
            cout << "Numero de colunas da primeira matriz é diferente do numero de linhas da segunda matriz";
            return m;
        }

    Matriz produto(m.size(), this[0].size());

        for(long unsigned int i = 0; i < this[0].size(); i++){
            for(long unsigned int j = 0; j < this->size(); j++){
                for(long unsigned int h = 0; j < this[0].size(); h++){
                    produto[i][j] += (*this)[i][h] * m[h][j];
                    cout << produto[i][j];
                }
            }
        }
        return produto; //retorna cópia, variavel criada é excluida ao fim da execução.

    }


Matriz Matriz::operator + (Matriz m){
        if(this->size() != m.size() && this[0].size() != m[0].size()) { //Se as matrizes não tiverem o msm tamanho fudeu!!
            cout <<"Matrizes tem tamanhos diferentes";
            return m;
        }

        Matriz produto(this->size(), this[0].size());

        for(long unsigned int i = 0; i < this->size(); i++){
            for(long unsigned int j = 0; j < this[0].size(); j++){
                produto[i][j] = (*this)[i][j] + m[i][j];
            }
        }
        return produto;
    }


Matriz transladarObjeto(double dX, double dY) {
    Matriz matrizTranslacao = new Matriz(3,3);

    matrizTranslacao[0][0] = 1; matrizTranslacao[0][1] = 0; matrizTranslacao[0][2] = dX;
    matrizTranslacao[1][0] = 0; matrizTranslacao[1][1] = 1; matrizTranslacao[1][2] = dY;
    matrizTranslacao[2][0] = 0; matrizTranslacao[2][1] = 0; matrizTranslacao[2][2] = 1;

    return matrizTranslacao * this->matriz;
}
