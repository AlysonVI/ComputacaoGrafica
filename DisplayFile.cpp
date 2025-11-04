#include "DisplayFile.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <QVector>

DisplayFile::~DisplayFile(){
    for(auto& obj : objects) delete obj;
}

void DisplayFile::add(Drawable* obj) {
    objects.append(obj);
}

void DisplayFile::drawAll(QPainter& painter) const {
    for(auto obj : objects)
        obj->draw(painter);
}

void DisplayFile::printAll() const{
    for(auto obj : objects)
        std::cout << "Objeto " << obj->getNome().toStdString() << "\n";
}
Drawable* DisplayFile::getObject(int n){
    return objects[n];
}

void DisplayFile::triggerTranslate(){
    Ponto centroWindow = getObject(0)->getObjectAverage();
    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->transformObject(-centroWindow.getX(), -centroWindow.getY());
    }
}

/*void DisplayFile::triggerRotate(double theta){
    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->rotateObject(-theta);
    }
}*/

void DisplayFile::applyGlobalTransform(double theta) {
    Matriz globalMatrix = getWorldToCameraMatrix(theta);

    for(auto&obj : objects){
        if(obj->getType() == ObjectType::Camera) continue;
        obj->applyMatrix(globalMatrix);
    }
}
Matriz DisplayFile::getWorldToCameraMatrix(double theta) {//matriz global para fazer translaçãp para centro e rotação baseado no angulo calculado antes (relativeToX)
    Ponto centroCamera = getObject(0)->getObjectAverage();
    double cx = centroCamera.getX();
    double cy = centroCamera.getY();


    Matriz T(3,3), R(3,3);
    T = T.getTransformMatrix(-cx, -cy);
    R = R.getRotateMatrix(-theta);

    Matriz globalMatrix = R * T;
    return globalMatrix;
}

void DisplayFile::triggerNormalize(double Wxmax, double Wxmin, double Wymax, double Wymin) {


    for (auto& obj : objects) {
        if(obj->getType() == ObjectType::Camera) continue;
        obj->normalizeObject(Wxmin, Wxmax, Wymin, Wymax);
    }
}

void DisplayFile::triggerViewport(double Vxmax, double Vxmin, double Vymax, double Vymin) {


    for (auto& obj : objects) {
        if(obj->getType() == ObjectType::Camera) continue;
        obj->viewportObject(Vxmin, Vxmax, Vymin, Vymax);
    }
}

// ---------------------------------------
// LEANDRO, IGNORE ESSA FUNCAO POR COMPLETO, AMANHÃ VOU ARRUMAR AS BOSTA Q O GEMINI FEZ AQUI
// --------------------------------------

void loadModelFromFile(const QString &filePath) {
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
