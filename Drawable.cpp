#include <memory>
#include <iostream>
#include "Drawable.h"
#include "Linha.h"

using namespace std;

Drawable::Drawable(const QString& n, ObjectType t, const QVector<Ponto>& pts)
    : nome(n), type(t), points(pts) {}

QVector<QPointF>* Drawable::getQPoints() {
    QVector<QPointF> *pointerToVector= new QVector<QPointF>;
    for(auto& aux : normPoints){
        pointerToVector->append(*(aux.convertToQPointF()));
    }
    return pointerToVector;
}

void Drawable::transformObject(double dX, double dY, double dZ) {
    for(auto& aux: points) {
        aux.transformPoint(dX, dY, dZ);
    }
}

void Drawable::scaleObject(double sX, double sY, double sZ) {
    Ponto avgPoint = getObjectAverage();
    this->goToOrigin(avgPoint);

    for(auto& aux: points) {
        aux.scalePoint(sX, sY, sZ);
    }
    this->returnFromOrigin(avgPoint);
}

void Drawable::rotateObjectX(double ang) {
    Ponto avgPoint = getObjectAverage();
    this->goToOrigin(avgPoint);

    for(auto& aux: points) {
        aux.rotatePointX(ang);
    }
    this->returnFromOrigin(avgPoint);
}

void Drawable::rotateObjectY(double ang) {
    Ponto avgPoint = getObjectAverage();
    this->goToOrigin(avgPoint);

    for(auto& aux: points) {
        aux.rotatePointY(ang);
    }
    this->returnFromOrigin(avgPoint);
}

void Drawable::rotateObjectZ(double ang) {
    Ponto avgPoint = getObjectAverage();
    this->goToOrigin(avgPoint);

    for(auto& aux: points) {
        aux.rotatePointZ(ang);
    }
    this->returnFromOrigin(avgPoint);
}

// Retorna o ponto da média entre todos os pontos do objetos, em todas as coordenadas (pode ser usado para retornar o centro da camera)
Ponto Drawable::getObjectAverage() {
    double somaX = 0, somaY = 0, somaZ = 0;

    for(auto& ponto: points) {
        somaX += ponto.getX();
        somaY += ponto.getY();
        somaZ += ponto.getZ();
    }
    int numPoints = points.size();
    return Ponto(somaX/numPoints, somaY/numPoints, somaZ/numPoints);
}

// transporta matriz pro 0,0
void Drawable::goToOrigin(Ponto p) {

    transformObject(-p.getX(), -p.getY(), -p.getZ());
}

// tras objeto de volta do 0,0
void Drawable::returnFromOrigin(Ponto p) {

    transformObject(p.getX(), p.getY(), p.getZ());
}

void Drawable::projectObject(double d) {

    Matriz MPer(4,4);

    MPer[0][0] = 1; MPer[0][1] = 0; MPer[0][2] = 0; MPer[0][3] = 0;
    MPer[1][0] = 0; MPer[1][1] = 1; MPer[1][2] = 0; MPer[1][3] = 0;
    MPer[2][0] = 0; MPer[2][1] = 0; MPer[2][2] = 1; MPer[2][3] = 0;
    MPer[3][0] = 0; MPer[3][1] = 0; MPer[3][2] = 1/d; MPer[3][3] = 0;
    /*
    if(normPoints.empty()) {
        for (auto& ponto : points) {
            normPoints.append(ponto);
        }
    }
    */
    for (auto& ponto : normPoints){
        Matriz pontoMatriz(4,1);
        pontoMatriz[0][0] = ponto.getX();
        pontoMatriz[1][0] = ponto.getY();
        pontoMatriz[2][0] = ponto.getZ();
        pontoMatriz[3][0] = 1;

        Matriz MResultado = MPer * pontoMatriz;

        double x = MResultado[0][0];
        double y = MResultado[1][0];
        double z = MResultado[2][0];
        double w = MResultado[3][0];
        if (w != 0){
            x /= w;
            y /= w;
            z /= w;
        }

        ponto = Ponto(x, y, z);
    }
}

void Drawable::normalizeObject(double Wxmin, double Wxmax, double Wymin, double Wymax) {
    /*
    if(normPoints.empty()) {
        for (auto& ponto : points) {
            normPoints.append(ponto);
        }
    }
    */
    for (auto& ponto : normPoints) {
        ponto.toSCN(Wxmin, Wxmax, Wymin, Wymax, true);
    }
}

void Drawable::viewportObject(double Vxmin, double Vxmax, double Vymin, double Vymax) {
    for (auto& ponto : normPoints) { // MUDE ESSA SEÇAO DE points PARA clippedPoints PARA A VIEWPORT DOS PONTOS CLIPADOS FUNCIONAR
        ponto.toViewport(Vxmin, Vxmax, Vymin, Vymax, true);
    }
}

void Drawable::applyMatrix(Matriz &M) {
    //normPoints.clear();
    for (auto& p : points) {
        Matriz pt(4,1);
        pt[0][0] = p[0][0];
        pt[1][0] = p[1][0];
        pt[2][0] = p[2][0];
        pt[3][0] = 1;

        pt = M * pt;

        p[0][0] = pt[0][0];
        p[1][0] = pt[1][0];
        p[2][0] = pt[2][0];
        //normPoints.append(Ponto(pt[0][0], pt[1][0], pt[2][0]));
    }
}

void Drawable::applyViewMatrix(Matriz &M){
    normPoints.clear();
    for (auto& p : points) {
        Matriz pt(4,1);
        pt[0][0] = p.getX();
        pt[1][0] = p.getY();
        pt[2][0] = p.getZ();
        pt[3][0] = 1;

        pt = M * pt;
        normPoints.append(Ponto(pt[0][0], pt[1][0], pt[2][0]));
    }
}
// Tem como entrada o retangulo onde ocorrera o clipping (geralmente vai ser as coordenadas da window), assim como dois pontos
// Então, a funcao calcula se a linha formada pelos pontos aparece na tela.
// Daí, retorna vetor de pontos vazio se estiver completamnete fora,
// ou retorna vetor de pontos dos pontos ja clipados, pra estar dentro do espaço informado
QVector<Ponto> Drawable::clipLine(double X_MIN, double X_MAX, double Y_MIN, double Y_MAX, const Ponto& p1, const Ponto& p2) {
    double x1 = p1.getX(), y1 = p1.getY();
    double x2 = p2.getX(), y2 = p2.getY();

    // códigos de região
    const int DENTRO = 0;   // 0000
    const int ESQUERDA = 1; // 0001
    const int DIREITA = 2;  // 0010
    const int BAIXO = 4;    // 0100
    const int CIMA = 8;     // 1000

    int codigo1 = this->computeOutCode(x1, y1, X_MIN, X_MAX, Y_MIN, Y_MAX);
    int codigo2 = this->computeOutCode(x2, y2, X_MIN, X_MAX, Y_MIN, Y_MAX);

    while(true) {
        // Caso 1. Segmento completamente contido na window
        if(codigo1 == DENTRO && codigo2 == DENTRO) {
            QVector<Ponto> linha;
            linha.append(Ponto(x1,y1));
            linha.append(Ponto(x2,y2));
            return linha;
        }

        // Caso 2. Segmento completamente fora da window
        else if((codigo1 & codigo2) != DENTRO) {
            QVector<Ponto> linha;
            return linha;
        }

        // Caso 3. Segmento parcialmente contido na window
        else {
            double xNovo, yNovo;
            int codigoFora = (codigo1 != DENTRO) ? codigo1 : codigo2;

            // Calculate intersection point
            if (codigoFora & CIMA) { // Point is above the clip window
                xNovo = x1 + (x2 - x1) * (Y_MIN - y1) / (y2 - y1);
                yNovo = Y_MIN;
            } else if (codigoFora & BAIXO) { // Point is below the clip window
                xNovo = x1 + (x2 - x1) * (Y_MAX - y1) / (y2 - y1);
                yNovo = Y_MAX;
            } else if (codigoFora & DIREITA) { // Point is to the right of clip window
                yNovo = y1 + (y2 - y1) * (X_MAX - x1) / (x2 - x1);
                xNovo = X_MAX;
            } else if (codigoFora & ESQUERDA) { // Point is to the left of clip window
                yNovo = y1 + (y2 - y1) * (X_MIN - x1) / (x2 - x1);
                xNovo = X_MIN;
            }

            // Agora atualiza o ponto que estsava fora
            if (codigoFora == codigo1) {
                x1 = xNovo;
                y1 = yNovo;
                codigo1 = this->computeOutCode(x1, y1, X_MIN, X_MAX, Y_MIN, Y_MAX);
            } else {
                x2 = xNovo;
                y2 = yNovo;
                codigo2 = this->computeOutCode(x2, y2, X_MIN, X_MAX, Y_MIN, Y_MAX);
            }
        }
    }
}

// Computa o codigo de saída do ponto da reta, usado para clipping
int Drawable::computeOutCode(double x, double y, double X_MIN, double X_MAX, double Y_MIN, double Y_MAX) {
    // códigos de região
    const int DENTRO = 0;   // 0000
    const int ESQUERDA = 1; // 0001
    const int DIREITA = 2;  // 0010
    const int BAIXO = 4;    // 0100
    const int CIMA = 8;     // 1000

    int codigo = DENTRO;

    if (x < X_MIN)
        codigo |= ESQUERDA;
    else if (x > X_MAX)
        codigo |= DIREITA;
    if (y < Y_MIN)
        codigo |= CIMA;
    else if (y > Y_MAX)
        codigo |= BAIXO;

    return codigo;
}

QVector<Ponto> Drawable::clipLineZ(const Ponto& p1, const Ponto& p2) {
    QVector<Ponto> linha; // linha clipada resultante, que será retornada pelo método
    double zLimite = -0.1; // z mínimo de distância da camera para fazer o clipping

    // Caso 1: Ambos pontos dentro, linha está na tela
    if ((p1.getZ() <= zLimite) && (p2.getZ() <= zLimite)) {
        linha.append(p1);
        linha.append(p2);
        return linha;
    }

    // Caso 2: Ambos pontos fora, linha inteira atrás da câmera
    if ((p1.getZ() > zLimite) && (p2.getZ() > zLimite)) {
        //cout << "\np1.getZ() = " << p1.getZ() << ", p2.getZ() = " << p2.getZ();
        return linha; // Retorna vazio
    }

    // Caso 3: Atravessa o plano da câmera, então é necessário calcular o ponto de intersecção
    // Fórmula paramétrica da reta: P(t) = P1 + t * (P2 - P1)
    double t = (zLimite - p1.getZ()) / (p2.getZ() - p1.getZ()); // Isolando t para o eixo Z

    // X e Y do ponto de interseção
    double xNovo = p1.getX() + t * (p2.getX() - p1.getX());
    double yNovo = p1.getY() + t * (p2.getY() - p1.getY());
    double zNovo = zLimite; // Z forçado a estar no plano

    Ponto pNovo(xNovo, yNovo, zNovo);

    if (p1.getZ() <= zLimite) {
        // Vai de p1 (dentro) até o limite
        linha.append(p1);
        linha.append(pNovo);
    }
    else {
        // O começo tava fora, então vai do limite até p2 (dentro)
        linha.append(pNovo);
        linha.append(p2);
    }

    return linha;
}

double Drawable::getXfromPoints(int i) {
    if(i < this->points.size())
        return points[i].getX();
    cout<<"\nErro, indice informado maior que a quantidade de pontos do objeto\n";
    return 0;
}

double Drawable::getYfromPoints(int i) {
    if(i < this->points.size())
        return points[i].getY();
    cout<<"\nErro, indice informado maior que a quantidade de pontos do objeto\n";
    return 0;
}

double Drawable::getZfromPoints(int i) {
    if(i < this->points.size())
        return points[i].getZ();
    cout<<"\nErro, indice informado maior que a quantidade de pontos do objeto\n";
    return 0;
}

void Drawable::clipObjectZ() {
    QVector<Ponto> clippedPoints;

    for (int i = 0; i < normPoints.size() - 1; i += 2) {
        if (i + 1 >= normPoints.size()) break;

        Ponto p1 = normPoints.at(i);
        Ponto p2 = normPoints.at(i+1);

        QVector<Ponto> linhaZ = clipLineZ(p1, p2);

        // linha dentro da câmera
        if (linhaZ.size() >= 2) {
            clippedPoints.append(linhaZ[0]);
            clippedPoints.append(linhaZ[1]);
        }
    }
    this->normPoints = clippedPoints;
}

// Tem como entrada as coordenadas do retangulo de corte (geralmente vai ser as coordenadas da window normalizada)
// Funçao computa o clipping de cada linha formada pelos pontos no vetor pointws do objeto, de forma sequencial
// Todas as linhas feitas a partir desse processo são clippadas e salvas no vetor normPoints, em cada objeto
void Drawable::clipObjectXY(double X_MAX, double X_MIN, double Y_MAX, double Y_MIN) {
    QVector<Ponto> clippedPoints;

    for (int i = 0; i < normPoints.length() - 1; i += 2) {
        Ponto p1 = normPoints.at(i);
        Ponto p2 = normPoints.at(i+1);

        // agora com a linha clipada no plano Z, fazemos o cliping no plano X e Y normalmente
        QVector<Ponto> linhaXY = clipLine(X_MIN, X_MAX, Y_MIN, Y_MAX, p1, p2);

        if(linhaXY.size() >= 2) { // despreza se a linha for nula, ou seja, fora da tela
            clippedPoints.append(linhaXY[0]);
            clippedPoints.append(linhaXY[1]);
        }
    }

    this->normPoints = clippedPoints;
}
