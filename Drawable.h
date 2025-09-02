#ifndef DRAWABLE_H
#define DRAWABLE_H


#include <QPainter>

#include <QPainter>
#include <QVector>
#include <QPointF>
#include <QString>
#include <iostream>

enum class ObjectType {
    Ponto,
    Linha,
    Poligono
};

class Drawable {
protected:
    QString nome;
    ObjectType type;
    QVector<QPointF> points;
public:
    Drawable(const QString& n, ObjectType t, const QVector<QPointF>& pts);
    virtual ~Drawable() {}

    QString getNome() const { return nome; }
    ObjectType getType() const { return type; }
    QVector<QPointF> getPoints() const { return points; }

    virtual void draw(QPainter& painter) const = 0;
};

#endif
