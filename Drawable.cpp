#include "Drawable.h"

Drawable::Drawable(const QString& n, ObjectType t, const QVector<QPointF>& pts)
    : nome(n), type(t), points(pts) {}
