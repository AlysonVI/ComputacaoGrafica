#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QString>
#include <iostream>
#include "Ponto.h"

enum class ObjectType {
    Linha,
    Polygon,
    Camera,
    Castelo
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
    virtual double getVariable()= 0; //Preciso para chamar no getObject(0) posso mudar

    void transformObject(double dX, double dY);
    void scaleObject(double sX, double sY);
    void rotateObject(double ang);

    void viewportObject(double Vxmin, double Vxmax, double Vymin, double Vymax);
    void normalizeObject(double Wxmin, double Wxmax, double Wymin, double Wymax);
    void applyMatrix(Matriz &M);
    vector<double>* getObjectAverage();
    void goToOrigin(vector<double>*);
    void returnFromOrigin(vector<double>*);
};

#endif
