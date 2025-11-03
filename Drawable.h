#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QString>
#include <iostream>
#include "Ponto.h"

class Linha;

enum class ObjectType {
    Linha,
    Polygon,
    Camera,
    Castelo,
    Curva
};

class Drawable {
protected:
    QString nome;
    ObjectType type;
    QVector<Ponto> points; //Listagem de pontos (aquilo q é usado nos métodos .draw())
    QVector<Ponto> normPoints; //Pontos SCN
public:
    Drawable(const QString& n, ObjectType t, const QVector<Ponto>& pts);
    virtual ~Drawable() {}

    QString getNome() const { return nome; }
    ObjectType getType() const { return type; }
    QVector<Ponto> getPoints() const { return points; }
    QVector<QPointF> *getQPoints();
    virtual void draw(QPainter& painter)= 0; //draw a ser definido (implementação na herança)


    void transformObject(double dX, double dY, double dZ);
    void scaleObject(double sX, double sY, double sZ);
    void rotateObjectX(double ang);
    void rotateObjectY(double ang);
    void rotateObjectZ(double ang);

    void viewportObject(double Vxmin, double Vxmax, double Vymin, double Vymax);
    void normalizeObject(double Wxmin, double Wxmax, double Wymin, double Wymax);
    void applyMatrix(Matriz &M);
    Ponto getObjectAverage();
    void goToOrigin(Ponto p);
    void returnFromOrigin(Ponto p);

    std::unique_ptr<Linha> clipLine(const Ponto& p1, const Ponto& p2); // funciona para ponto tb, é só parrar pq e p2 iguais
    int computeOutCode(double x, double y, double X_MIN, double X_MAX, double Y_MIN, double Y_MAX);
    double getXfromPoints(int i);
    double getYfromPoints(int i);
    double getZfromPoints(int i);

};

#endif
