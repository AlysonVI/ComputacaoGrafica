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
    ui->setupUi(this);
    viewportX= 500;
    viewportY= 500;
    setFixedSize(viewportX, viewportY);

    //painter.setViewport(-worldX,  worldY, this->width(), this->height());
    pToCamera= new Camera("c1", QVector<Ponto>{
                                     {0, 0}, {0, 500}, {500, 500}, {500, 0}
                                 });

    //pToCamera->rotateCamera(250,250); //Ponto "up"
    pToCamera->scaleObject(1,1);
    pToCamera->transformObject(-180,-270); //Camera

}

void MainWindow::criarMundo(DisplayFile& display){

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


    display.getObject(5)->transformObject(0, 0);
    display.getObject(5)->rotateObject(M_PI);
    display.getObject(5)->scaleObject(0.7,0.7);

    display.getObject(6)->transformObject(0, 0);
    //display.getObject(6)->rotateObject(M_PI/4);
    display.getObject(6)->scaleObject(5,5);

}

void MainWindow::paintEvent(QPaintEvent* event){
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    DisplayFile display;

    display.add(new Camera(*pToCamera));

    criarMundo(display);

    QVector<Ponto> pPontosCamera= pToCamera->getPoints();
    double Wxmin = pPontosCamera[0][0][0];
    double Wymin = pPontosCamera[0][1][0];
    double Wxmax = pPontosCamera[2][0][0];
    double Wymax = pPontosCamera[2][1][0];
    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform(pToCamera->angleRelativeToX);


    //Normaliza todos os pontos para SCN eu acho
    display.triggerNormalize(Wxmax, Wxmin, Wymin, Wymax); // window

    //Transforma SCN para viewport
    display.triggerViewport(width(), 0, height(), 0);

    //painter.setWindow(-worldX, worldY, this->width(), this->height());

    display.printAll();
    display.drawAll(painter);
    cout << "Update event\n";
}
MainWindow::~MainWindow()
{
    delete ui;
    delete pToCamera;
}

void MainWindow::on_right_clicked()
{
    //botão deve mover camera para direita
    pToCamera->transformObject(10,0);
    update();
}


void MainWindow::on_down_clicked()
{
    //botão deve mover camera para baixo
    pToCamera->transformObject(0,10);
    update();
}


void MainWindow::on_left_clicked()
{
    //botão deve mover camera para a esquerda
    pToCamera->transformObject(-10,0);
    update();
}


void MainWindow::on_up_clicked()
{
    //botão deve mover camera para cima
    pToCamera->transformObject(0,-10);
    update();
}

