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

    //painter.setViewport(-worldX,  worldY, this->width(), this->height());
    Camera* pToCamera= new Camera("c1", QVector<Ponto>{
                         {0, 0}, {0, 500}, {500, 500}, {500, 0}
                                         });
    display.add(pToCamera);

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

    pToCamera->rotateCamera(500,0);

    display.getObject(0)->transformObject(500,350); //Camera

    display.getObject(5)->transformObject(500, 200);
    //display.getObject(5)->rotateObject(M_PI);
    display.getObject(5)->scaleObject(0.7,0.7);

    display.getObject(6)->transformObject(50, 150);
    //display.getObject(6)->rotateObject(M_PI/4);
    display.getObject(6)->scaleObject(5,5);


    //painter.setWindow(-worldX, worldY, this->width(), this->height());

    display.printAll();
    ui->setupUi(this);

}
void MainWindow::paintEvent(QPaintEvent* event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform();

    //Normaliza todos os pontos para SCN eu acho
    display.triggerNormalize(500, 0,500,0); // window

    //Transforma SCN para viewport
    display.triggerViewport(width(), height());

    display.drawAll(painter);
}
MainWindow::~MainWindow()
{
    delete ui;
}
