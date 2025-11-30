#include "ModeloOBJ.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QDebug>  // Use QDebug/qWarning em vez de iostream
#include <QFileInfo> // Para pegar o nome do arquivo

ModeloOBJ::ModeloOBJ(const QString &filePath)
    : Drawable("OBJ", ObjectType::OBJ, {}) {
    loadModel(filePath);
}

void ModeloOBJ::loadModel(const QString &filePath) {
    this->points.clear();
    this->indicesArestas.clear();

    QFile file(filePath);

    // Abre arquivo em read-only
    // Nova versão de checagem de erro
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // qWarning() é o "cout" do Qt para erros
        qWarning() << "ERRO: Não foi possível abrir o arquivo:" << filePath;
        qWarning() << "Motivo do erro:" << file.errorString(); // <-- ISSO É O MAIS IMPORTANTE
        return;
    }

    // Se chegou aqui, o arquivo abriu!
    qDebug() << "Arquivo aberto com sucesso:" << filePath;

    // Leitor de arquivos
    QTextStream in(&file);

    // Leitor lê linha por linha
    while (!in.atEnd()) {
        QString linha = in.readLine().trimmed(); // Lê linha e apara espaços em branco

        if (linha.isEmpty() || linha.startsWith('#')) { // Pula linhas em branco e comentários
            continue;
        }

        QStringList partes = linha.split(' ', Qt::SkipEmptyParts); // Separa linha em "palavras", separadas por espaço
        if (partes.isEmpty()) {
            continue;
        }

        QString tipo = partes.at(0); // Pega o identificador do tipo ("v", "f", "vn", etc)

        // --- Lógica de PARSING específica de OBJ ---

        if (tipo == "v") { // vértice
            if (partes.count() < 4) continue; // v x y z
            double x = partes.at(1).toDouble();
            double y = partes.at(2).toDouble();
            double z = partes.at(3).toDouble();

            points.append(Ponto(x, y, z));
        }
        else if (tipo == "f") { // face
            if (partes.count() < 4) continue; // f v1 v2 v3 ...

            QVector<int> faceIndices;
            for (int i = 1; i < partes.count(); i++) {
                QString faceIndiceStr = partes.at(i).split('/').at(0);

                // .obj usa indice começando no 1, logo subtrai 1 para normalizar
                int faceIndice = faceIndiceStr.toInt() - 1;
                faceIndices.append(faceIndice);
            }

            for (int i = 0; i < faceIndices.size(); i++) {
                indicesArestas.append(faceIndices[i]);
                indicesArestas.append(faceIndices[(i + 1) % faceIndices.size()]);
            }
        }
    }

    file.close();
}

void ModeloOBJ::clipObjectZ() {
    if (indicesArestas.isEmpty()) return;

    QVector<Ponto> clippedPoints;

    // Percorre indicesArestas (2 em 2)
    for (int i = 0; i < indicesArestas.length() - 1; i += 2) {

        Ponto p1 = normPoints.at(indicesArestas[i]);
        Ponto p2 = normPoints.at(indicesArestas[i+1]);

        QVector<Ponto> linhaZ = clipLineZ(p1, p2);

        // linha dentro da câmera
        if(linhaZ.size() >= 2) {
            clippedPoints.append(linhaZ[0]);
            clippedPoints.append(linhaZ[1]);
        }
    }

    this->normPoints = clippedPoints;
    this->indicesArestas.clear();
}

// a mesma coisa que o clipObject de drawable, mas usa arestas ao invés de normPoints, para previnir erros
void ModeloOBJ::clipObjectXY(double X_MAX, double X_MIN, double Y_MAX, double Y_MIN) {
    if (indicesArestas.isEmpty()) return;

    QVector<Ponto> clippedPoints;

    // Percorre indicesArestas (2 em 2)
    for (int i = 0; i < indicesArestas.length() - 1; i += 2) {

        Ponto p1 = normPoints.at(indicesArestas[i]);
        Ponto p2 = normPoints.at(indicesArestas[i+1]);

        // agora com a linha clipada no plano Z, fazemos o cliping no plano X e Y normalmente
        QVector<Ponto> linhaXY = clipLine(X_MIN, X_MAX, Y_MIN, Y_MAX, p1, p2);

        if(linhaXY.size() >= 2) { // despreza se a linha for nula, ou seja, fora da tela
            clippedPoints.append(linhaXY[0]);
            clippedPoints.append(linhaXY[1]);
        }
    }

    this->normPoints = clippedPoints;
}

void ModeloOBJ::draw(QPainter& painter) {
    if (normPoints.isEmpty()) {
        return;
    }

    painter.setPen(Qt::blue);
    for (int i = 0; i < normPoints.size() - 1; i += 2) {
        QPointF p1(normPoints[i].getX(), normPoints[i].getY());
        QPointF p2(normPoints[i+1].getX(), normPoints[i+1].getY());

        painter.drawLine(p1, p2);
    }

    painter.setPen(Qt::green);
}

