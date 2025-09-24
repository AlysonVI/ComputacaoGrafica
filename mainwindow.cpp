#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include "Camera.h"
#include <QPainter>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    worldX= 500;
    worldY= 500;
    setFixedSize(worldX, worldY);

    QPainter painter(this);

    //painter.setViewport(-worldX,  worldY, this->width(), this->height());

    display.add(new Camera("c1", QVector<Ponto>{
                                     {0, 0}, {0, 500}, {500, 500}, {500, 0}
                                 }));

    display.add(new Linha("cima", Ponto(0,0), Ponto(100,0   )));
    display.add(new Linha("direita", Ponto(100,0), Ponto(100,100)));
    display.add(new Linha("baixo", Ponto(100,100), Ponto(0,100)));
    display.add(new Linha("esquerda",  Ponto(0,100), Ponto(0,0)));

    display.add(new Polygon("rect", QVector<Ponto>{
            {170, 0}, {220, 100}, {120, 100}
        }));

    display.add(new Polygon("new rect", QVector<Ponto>{
                                                   {120, 0}, {120, 100}, {220, 100}, {220, 0}
                                    }));

    display.getObject(5)->transformObject(100, 200);
    display.getObject(5)->rotateObject(M_PI);
    display.getObject(5)->scaleObject(0.7,0.7);

    display.getObject(6)->transformObject(50, 150);
    display.getObject(6)->rotateObject(M_PI/4);
    display.getObject(6)->scaleObject(5,5);

    //painter.setWindow(-worldX, worldY, this->width(), this->height());

    display.printAll();
    ui->setupUi(this);

}
void MainWindow::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    Ponto *p= new Ponto(50, 50);
    p->draw(painter);
    display.drawAll(painter);
}
MainWindow::~MainWindow()
{
    delete ui;
}
