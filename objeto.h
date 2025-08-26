#ifndef OBJETO_H
#define OBJETO_H
#include <linha.h>
#include <ponto.h>
#include <vector>
#include <string>

using namespace std;

class Objeto
{
public:

    string nome;
    int numLinhas;

    std::vector<Linha> vetorDeLinhas;


    Objeto();
    Objeto(string nome);
    ~Objeto();

    void adicionaLinha(Linha l);

    void mostraLinhas();
};

#endif // OBJETO_H
