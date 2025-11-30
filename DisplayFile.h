#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include "Drawable.h"
#include <QVector>
#include "Camera.h"

class DisplayFile {
    QVector<Drawable*> objects; //display file
public:
    ~DisplayFile();
    void add(Drawable* obj);
    void drawAll(QPainter& painter) const;
    void printAll() const;

    void triggerTranslate();//Quando faz na window
    void triggerPerspective(double d);
    void triggerNormalize(double Wxmax, double Wxmin, double Wymax, double Wymin);
    void triggerZClipping();
    void triggerXYClipping(double Wxmax, double Wxmin, double Wymax, double Wymin);
    void triggerViewport(double Vxmax, double Vxmin, double Vymax, double Vymin);
    void applyGlobalTransform(Camera* pToCamera);
    Matriz getWorldToCameraMatrix(Camera* pToCamera);
    Drawable* getObject(int n);
};


#endif
