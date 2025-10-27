#ifndef CASTELO_H
#define CASTELO_H

#include "Drawable.h"

class Castelo : public Drawable {
public:
    Castelo(const Ponto& p);
    void draw(QPainter& painter) override;
};

#endif // CASTELO_H



