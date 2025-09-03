#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>

// Garrafa garrafa1 = new Garrafa(40, 50);
// display.add(garrafa1);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    worldX= 600;
    worldY= 600;
    setFixedSize(worldX, worldY);

    QPainter painter(this);

    painter.setViewport(0, 0, this->width(), this->height());
    painter.setWindow(-worldX / 2, worldY / 2, worldX, worldY);
    //casinha 1
    display.add(new Polygon("quadrado", QVector<QPointF>{
                                            {50, 200}, {150, 200},
                                            {150, 300}, {50, 300}
                                         }));

    //telhado1
    display.add(new Polygon("triangulo", QVector<QPointF>{
                                     {250, 250}, {300, 300}, {200, 300}
                                 }));

    display.add(new Linha("linha", QPointF(400, 200), QPointF(450, 270)));

    display.add(new Ponto("ponto", QPointF(400, 400)));

    display.printAll();
    ui->setupUi(this);



}
void MainWindow::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    display.drawAll(painter);
}
MainWindow::~MainWindow()
{
    delete ui;
}
