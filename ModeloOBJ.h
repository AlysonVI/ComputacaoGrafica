#ifndef MODELOOBJ_H
#define MODELOOBJ_H

#include "Drawable.h"
#include <QVector>

class ModeloOBJ : public Drawable {
private:
    QVector<int> indicesArestas; // Contém índices das arestas para facilitar clipping e draw
public:
    ModeloOBJ(const QString &filePath);
    void loadModel(const QString &filePath); // Carrega objeto do tipo obj dos arquivos
    void draw(QPainter& painter) override;
    void clipObjectZ() override;
};

#endif
