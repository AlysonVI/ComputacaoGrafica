#include "mainwindowalyson.h"

#include <QApplication>
#include "QPainter"

int main(int argc, char *argv[])
{
    QPainter painter(this);

    painter.setViewport(0, 0, this->width(), this->height());
    painter.setWindow(-worldX / 2, -worldY / 2, worldX, worldY);

    QApplication a(argc, argv);
    MainWindowAlyson w;
    w.show();
    painter.drawLine(QPoint(10,10), QPoint(210,210));
    return a.exec();
}
