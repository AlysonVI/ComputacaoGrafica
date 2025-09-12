#include "Ampulheta.h"

Ampulheta::Ampulheta(double x, double y)
    : Drawable{{p1, p2}}
Ampulheta::draw(QPainter& painter){
    // (0,0),(100,0),(100,10),(0,10),
    painter.drawLine(*(points[0].convertToQPointF()), *(points[1].convertToQPointF()));
}
