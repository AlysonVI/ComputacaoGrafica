#ifndef IMPLEMENT_H
#define IMPLEMENT_H

#include <QWidget>
#include "DisplayFile.h"

//Canvas extra para teste (fora da main window)
class MyCanvas : public QWidget {
    Q_OBJECT
    DisplayFile display;
public:
    MyCanvas();

protected:
    void paintEvent(QPaintEvent* event) override;
};


#endif
