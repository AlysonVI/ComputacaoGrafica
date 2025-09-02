#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    worldX= 400;
    worldY= 400;
    setFixedSize(worldX, worldY);

    QPainter painter(this);

    painter.setViewport(0, 0, this->width(), this->height());
    painter.setWindow(-worldX / 2, worldY / 2, worldX, worldY);

    offset = 100;

    //casinha 1
    display.add(new Polygon("quadrado", QVector<QPointF>{
                                            {0, 200}, {100, 200},
                                            {100, 300}, {0, 300}
                                         }));

    //telhado1
    display.add(new Polygon("triangulo", QVector<QPointF>{
                                     {50, 100}, {100, 200}, {000, 200}
                                 }));

    //bandeira 1
    display.add(new Linha("linha", QPoint(50, 100), QPoint(50, 50)));

    display.add(new Polygon("quadrado", QVector<QPointF>{
                                            {50, 75}, {50, 50},
                                            {80, 50}, {80, 75}
                                        }));

    //bandeira 2
    display.add(new Linha("linha", QPoint(349, 100), QPoint(349, 50)));

    display.add(new Polygon("quadrado", QVector<QPointF>{
                                            {349, 75}, {349, 50},
                                            {379, 50}, {379, 75}
                                        }));


    //casinha 2
    display.add(new Polygon("quadrado", QVector<QPointF>{
                                            {299, 200}, {399, 200},
                                            {399, 300}, {299, 300}
                                        }));

    //telhado 2
    display.add(new Polygon("triangulo", QVector<QPointF>{
                                             {349, 100}, {399, 200}, {299, 200}
                                         }));


    // muro
    display.add(new Linha("linha", QPoint(100, 220), QPoint(299, 220)));
    display.add(new Linha("linha", QPoint(100, 300), QPoint(299, 300)));

    //portao
    display.add(new Polygon("quadrado", QVector<QPointF>{
                                            {170, 300}, {170, 250},
                                            {230, 250}, {230, 300}
                                        }));

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
