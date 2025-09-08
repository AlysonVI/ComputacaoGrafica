#include "Matriz.h"
#include <vector>
using namespace std;

    Matriz::Matriz(int& l, int& c) :
        vector<vector<double>>(l,c) {}

    Matriz operator * (Matriz m){

        if(this->l != m->c) {
            cout << "Numero de colunas da primeira matriz é diferente do numero de linhas da segunda matriz";
            return NULL;
        }
        Matriz aux(m->l, this->c);

        for(int i = 0; i< this->c; i++){
            for(int j = 0; j < this->l; j++){
                for(int h=0; j < this->c; h++){
                    aux[i][j] += this[i][h] * m[h][j];
                }
            }
        }
        return aux; //retorna cópia, variavel criada é excluida ao fim da execução.

    }


    Matriz operator + (Matriz m){
        if(this->l != m->l && this->c != m->c) { //Se as matrizes não tiverem o msm tamanho fudeu!!
            cout <<"Matrizes tem tamanhos diferentes";
        }

        Matriz aux(this->l, this->c);

        for(int i = 0; i < this->l; i++){
            for(int j = 0; j < this->c; j++){
                aux[i][j] = this[i][j] + m[i][j];
            }
        }
    }

