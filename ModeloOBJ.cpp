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
    this->faces.clear();

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

            // Adiciona essa face para a lista das faces
            faces.append(faceIndices);
        }
    }

    file.close();
}

void ModeloOBJ::draw(QPainter& painter) {
    if (normPoints.isEmpty()) {
        return;
    }
    for (const QVector<int>& face : faces) {

        // Itera para cada vertice no vetor da face
        for (int i = 0; i < face.count(); i++) {

            // Ponto inicial da linha
            int p1Indice = face.at(i);

            // Modulo (%) para conectar ultima vertice à primeira
            int p2Indice = face.at((i + 1) % face.count());

                // Pega os pontos 2D e desenha, fazendo projeção ortogonal
            QPointF p12D((normPoints.at(p1Indice)).getX(), (normPoints.at(p1Indice)).getY());
            QPointF p22D((normPoints.at(p2Indice)).getX(), (normPoints.at(p2Indice)).getY());

            painter.drawLine((p12D), (p22D));
        }
    }
}
