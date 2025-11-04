#include <memory>
#include <iostream>
#include "Drawable.h"
#include "Linha.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>

using namespace std;

Drawable::Drawable(const QString& n, ObjectType t, const QVector<Ponto>& pts)
    : nome(n), type(t), points(pts) {}

QVector<QPointF>* Drawable::getQPoints() {
    QVector<QPointF> *pointerToVector= new QVector<QPointF>;
    for(auto& aux : points){
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

Ponto Drawable::getObjectAverage() {
    double somaX = 0, somaY = 0, somaZ = 0;

    for(auto& aux: points) {
        somaX += aux.getX();
        somaY += aux.getY();
        somaZ += aux.getZ();
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

void Drawable::normalizeObject(double Wxmin, double Wxmax, double Wymin, double Wymax) {
    for (auto& ponto : points) {
        ponto.toSCN(Wxmin, Wxmax, Wymin, Wymax, true);

    }
}

void Drawable::viewportObject(double Vxmin, double Vxmax, double Vymin, double Vymax) {
    for (auto& ponto : points) {
        ponto.toViewport(Vxmin, Vxmax, Vymin, Vymax, true);

    }
}

void Drawable::applyMatrix(Matriz &M) {
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
    }
}

std::unique_ptr<Linha> Drawable::clipLine(const Ponto& p1, const Ponto& p2) {
    double x1 = p1.getX(), y1 = p1.getY();
    double x2 = p2.getX(), y2 = p2.getY();

    // calcula bordas
    double X_MIN = getXfromPoints(1); // x do ponto inferior esquerdo da camera
    double X_MAX = getXfromPoints(2); // x do ponto inferior direito da camera
    double Y_MIN = getYfromPoints(0); // y do ponto superior esquerdo da camera
    double Y_MAX = getYfromPoints(1); // y do ponto inferior esquerdo da camera

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
        if(codigo1 == DENTRO && codigo2 == DENTRO)
            return std::make_unique<Linha>("", Ponto(x1,y1), Ponto(x2,y2));

        // Case 2. Segmento completamente fora da window
        else if((codigo1 & codigo2) != DENTRO)
            return nullptr;

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

            // Now update the point that was outside.
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

// ---------------------------------------
// LEANDRO, IGNORE ESSA FUNCAO POR COMPLETO, AMANHÃ VOU ARRUMAR AS BOSTA Q O GEMINI FEZ AQUI
// --------------------------------------

void loadModel(const QString &filePath) {
    QFile file(filePath);

    // Abre arquivo em read-only
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        cout << "Erro. Arquivo não foi aberto. " << filePath;
        return;
    }

    // Leitor de arquivos
    QTextStream in(&file);

    // Leitor lê linha por linha
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed(); // Lê linha e apara espaços em branco

        if (line.isEmpty() || line.startsWith('#')) { // Pula linhas em branco e comentários
            continue;
        }

        QStringList parts = line.split(' ', Qt::SkipEmptyParts); // Separa linha em "palavras", separadas por espaço
        if (parts.isEmpty()) {
            continue;
        }

        QString type = parts.at(0); // Pega o identificador do tipo ("v", "f", "vn", etc)

        // --- Lógica de PARSING específica de OBJ ---

        if (type == "v") { // vértice
            if (parts.count() < 4) continue; // v x y z
            double x = parts.at(1).toFloat();
            double y = parts.at(2).toFloat();
            double z = parts.at(3).toFloat();

            // Store this vertex (e.g., in a QVector<QVector3D>)
            // myVertices.append(QVector3D(x, y, z));
            qDebug() << "Found vertex:" << x << y << z;

        } else if (type == "f") { // face
            if (parts.count() < 4) continue; // f v1 v2 v3

            // Note: .obj files are 1-indexed, so subtract 1
            int v1 = parts.at(1).split('/').at(0).toInt() - 1;
            int v2 = parts.at(2).split('/').at(0).toInt() - 1;
            int v3 = parts.at(3).split('/').at(0).toInt() - 1;

            // Store this face's indices (e.g., in a QVector<int>)
            // myFaces.append(v1);
            // myFaces.append(v2);
            // myFaces.append(v3);
            qDebug() << "Found face:" << v1 << v2 << v3;
        }
        // Alyson, add o resto dos tipos
    }

    file.close();

    // f() que redesenha o mundo
}

