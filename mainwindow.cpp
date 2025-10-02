#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
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
    pToCamera= new Camera("c1", QVector<Ponto>{
                         {0, 0}, {0, 500}, {500, 500}, {500, 0}
                                         });
    display.add(pToCamera);

    display.add(new Linha("cima", Ponto(0,0), Ponto(100,0   )));
    display.add(new Linha("direita", Ponto(100,0), Ponto(100,100)));
    display.add(new Linha("baixo", Ponto(100,100), Ponto(0,100)));
    display.add(new Linha("esquerda",  Ponto(0,100), Ponto(0,0)));

    display.add(new Polygon("triangulo", QVector<Ponto>{
            {170, 0}, {220, 100}, {120, 100}
        }));

    display.add(new Polygon("quadradao", QVector<Ponto>{
                                                {120, 0}, {120, 100}, {220, 100}, {220, 0}
                                    }));

    //pToCamera->rotateCamera(250,250);
    display.getObject(0)->scaleObject(1.2,1.2);
    display.getObject(0)->transformObject(-300,-400); //Camera

    display.getObject(5)->transformObject(0, 0);
    //display.getObject(5)->rotateObject(M_PI);
    display.getObject(5)->scaleObject(0.7,0.7);

    display.getObject(6)->transformObject(0, 0);
    //display.getObject(6)->rotateObject(M_PI/4);
    display.getObject(6)->scaleObject(5,5);


    //painter.setWindow(-worldX, worldY, this->width(), this->height());

    display.printAll();
    ui->setupUi(this);

    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform();

}
void MainWindow::paintEvent(QPaintEvent* event) {
    QMainWindow::paintEvent(event);
    QPainter painter(this);

    display.drawAll(painter);
}
MainWindow::~MainWindow()
{
    delete ui;
}
