#ifndef MODELOOBJ_H
#define MODELOOBJ_H

#include "Drawable.h"
#include <QVector>

class ModeloOBJ : public Drawable {
private:
    QVector<QVector<int>> faces;
public:
    ModeloOBJ(const QString &filePath);
    void loadModel(const QString &filePath); // carrega objeto do tipo obj dos arquivos
    void draw(QPainter& painter) override;
};

#endif // MODELOOBJ_H
