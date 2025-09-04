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
};


#endif
