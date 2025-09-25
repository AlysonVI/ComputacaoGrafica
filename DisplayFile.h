#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "Drawable.h"
#include <QVector>

class DisplayFile {
    QVector<Drawable*> objects; //display file
public:
    ~DisplayFile();
    void add(Drawable* obj);
    void drawAll(QPainter& painter) const;
    void printAll() const;

    void triggerTranslate();//Quando faz na window
    void triggerRotate();
    void triggerNormalize(double Wxmax, double Wxmin, double Wymax, double Wymin);
    void triggerViewport(double Vxmax, double Vymax);
    void applyGlobalTransform();
    Matriz getWorldToCameraMatrix();
    Drawable* getObject(int n);
};


#endif
