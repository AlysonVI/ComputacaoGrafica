#include "ModeloOBJ.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>

ModeloOBJ::ModeloOBJ(const QString &filePath)
    : Drawable("OBJ", ObjectType::OBJ, {}) {
    loadModel(filePath);
}

void ModeloOBJ::loadModel(const QString &filePath) {
    this->points.clear();
    this->faces.clear();

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

        QString tipo = parts.at(0); // Pega o identificador do tipo ("v", "f", "vn", etc)

        // --- Lógica de PARSING específica de OBJ ---

        if (tipo == "v") { // vértice
            if (parts.count() < 4) continue; // v x y z
            double x = parts.at(1).toDouble();
            double y = parts.at(2).toDouble();
            double z = parts.at(3).toDouble();

            points.append(Ponto(x, y, z));

            qDebug() << "Vertice encontrada: " << x << y << z;

        } else if (tipo == "f") { // face
            if (parts.count() < 4) continue; // f v1 v2 v3 ...

            QVector<int> faceIndices; // To store this single face
            for (int i = 1; i < parts.count(); ++i) {
                // Parse "v/vt/vn". We only want 'v'
                QString v_index_str = parts.at(i).split('/').at(0);

                // .obj is 1-indexed, QVector is 0-indexed. SUBTRACT 1.
                int index = v_index_str.toInt() - 1;
                faceIndices.append(index);
            }

            // Add this face (e.g., {0, 1, 2}) to our list of all faces
            m_faces.append(faceIndices);
        }
    }

    file.close();

    // f() que redesenha o mundo
}

void ModeloOBJ::draw(QPainter& painter) {
    // ⚠️ IMPORTANT: You must draw using 'normPoints', not 'points'.
    // 'normPoints' holds the normalized and viewport-transformed coordinates.
    // 'points' holds the original, raw coordinates.
    if (normPoints.isEmpty()) {
        return; // Nothing to draw
    }

    // Iterate over every FACE
    for (const QVector<int>& face : m_faces) {

        // Iterate over every VERTEX in *this* face
        for (int i = 0; i < face.count(); ++i) {

            // Get the index for the start-point of the line
            int p1_index = face.at(i);

            // Get the index for the end-point of the line
            // Use modulo (%) to wrap around (e.g., connect last vertex to first)
            int p2_index = face.at((i + 1) % face.count());

            // --- Safety Check ---
            if (p1_index >= normPoints.count() || p2_index >= normPoints.count()) {
                qWarning() << "OBJ face index out of bounds!";
                continue;
            }

            // Get the 2D points from the 'normPoints' vector
            const Ponto& p1 = normPoints.at(p1_index);
            const Ponto& p2 = normPoints.at(p2_index);

            // Draw the line for this edge of the face
            painter.drawLine(QPointF(p1.getX(), p1.getY()), QPointF(p2.getX(), p2.getY()));
        }
    }
}
