#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>
#include <math.h>
#include "Castelo.h"
// necessarios para debug
#include <memory>
#include "Drawable.h"
#include "Polygon.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    viewportX = this->width();
    viewportY = this->height();
    setFixedSize(viewportX, viewportY);

    //painter.setViewport(-worldX,  worldY, this->width(), this->height());
    pToCamera= new Camera("c1", QVector<Ponto>{
                                     {0, 0}, {0, 500}, {500, 500}, {500, 0}
                                 });

    //pToCamera->rotateCamera(250,250); //Ponto "up"
    pToCamera->transformObject(-100,-100); //Camera
    pToCamera->scaleObject(1.3,1.3); //Camera


}

void MainWindow::criarMundo(DisplayFile& display){

    Castelo* castelo1 = new Castelo(Ponto(200,200));
    Castelo* castelo2 = new Castelo(Ponto(70,250));
    Castelo* castelo3 = new Castelo(Ponto(300,400));

    display.add(castelo1);
    display.add(castelo2);
    display.add(castelo3);

    Polygon* borderRectangle = new Polygon("borderRectangle", QVector<Ponto>{
                                                                  {50, 50}, {50, 450}, {450, 450}, {450, 50}
                                                              });
    // Linha clipada 1
    display.add(borderRectangle);
    Ponto p11(500,300);
    Ponto p21(-50,-50);
    auto linha1 = borderRectangle->clipLine(p11, p21);
    if(linha1)
        display.add(linha1.release());

    // Linha clipada 2
    Ponto p12(60,80);
    Ponto p22(600,100);
    auto linha2 = borderRectangle->clipLine(p12, p22);
    if(linha2)
        display.add(linha2.release());

    // Linha clipada 3
    Ponto p13(300,300);
    Ponto p23(200,400);
    auto linha3 = borderRectangle->clipLine(p13, p23);
    if(linha3)
        display.add(linha3.release());

    castelo1->scaleObject(1.7, 1.7);
    castelo1->rotateObject(M_PI);

    castelo2->scaleObject(0.5, 0.5);
    castelo2->transformObject(0, 100);

    castelo3->rotateObject(-M_PI/5);


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

