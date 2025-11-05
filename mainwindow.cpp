#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>
#include <math.h>
#include "Castelo.h"
#include <memory>
#include "Drawable.h"
#include "Polygon.h"
#include "Curva.h"
#include "ModeloOBJ.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    viewportX = this->width();
    viewportY = this->height();
    setFixedSize(viewportX, viewportY);

    //painter.setViewport(-worldX,  worldY, this->width(), this->height());
    pToCamera = new Camera("c1", QVector<Ponto>{
                                     {0, 0}, {0, 500}, {500, 500}, {500, 0}
                                 });

    const double BORDA = 50; // Espessura da margem de desenho dentro da camera (retangulo de clipping)
    pToBorderRectangle = new Polygon("border", QVector<Ponto>{
                                     {pToCamera->getXfromPoints(0)+BORDA, pToCamera->getYfromPoints(0)+BORDA},
                                     {pToCamera->getXfromPoints(1)+BORDA, pToCamera->getYfromPoints(1)-BORDA},
                                     {pToCamera->getXfromPoints(2)-BORDA, pToCamera->getYfromPoints(2)-BORDA},
                                     {pToCamera->getXfromPoints(3)-BORDA, pToCamera->getYfromPoints(3)+BORDA}
                                 });

    // pToCamera->rotateCamera(250,250); //Ponto "up"
    pToCamera->transformObject(-100,-100,0); //Camera
    pToCamera->scaleObject(1.2,1.2,0); //Camera

    pToBorderRectangle->transformObject(20,10,0);
    pToBorderRectangle->scaleObject(1.2,1.2,0); //Borda
}

void MainWindow::criarMundo(DisplayFile& display){

    Castelo* castelo1 = new Castelo(Ponto(200,200));
    Castelo* castelo2 = new Castelo(Ponto(70,250));
    Castelo* castelo3 = new Castelo(Ponto(300,400));
    Curva* curva = new Curva("curva", Ponto(100,100), Ponto(200,300), Ponto(400,200), 5);

    display.add(castelo1);
    display.add(castelo2);
    display.add(castelo3);
    display.add(curva);


    // Linha clipada 1
    Ponto p11(500,300);
    Ponto p21(-50,-50);
    auto linha1 = pToBorderRectangle->clipLine(p11, p21); // Se substituir pToBorderRectangle por pToCamera, o clipping ocorrera na camera ao inves da borda
    if(linha1)
        display.add(linha1.release());

    // Linha clipada 2
    Ponto p12(60,80);
    Ponto p22(600,100);
    auto linha2 = pToBorderRectangle->clipLine(p12, p22);
    if(linha2)
        display.add(linha2.release());

    // Linha clipada 3
    Ponto p13(300,300);
    Ponto p23(200,400);
    auto linha3 = pToBorderRectangle->clipLine(p13, p23);
    if(linha3)
        display.add(linha3.release());

    castelo1->scaleObject(1.7, 1.7, 0);
    castelo1->rotateObjectX(M_PI);

    castelo2->scaleObject(0.5, 0.5, 0);
    castelo2->transformObject(0, 100, 0);

    castelo3->rotateObjectX(-M_PI/5);

    ModeloOBJ* modelo = new ModeloOBJ("C:/ProjetoCG/ComputacaoGrafica/006 - Charizard/Charizard.obj");
    display.add(modelo);
    //modelo->rotateObjectX(M_PI);
    modelo->rotateObjectY(M_PI/2);
    //modelo->rotateObjectZ(M_PI/4);
    modelo->scaleObject(15,15,15);
}

void MainWindow::paintEvent(QPaintEvent* event){
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    DisplayFile display;

    display.add(new Camera(*pToCamera));
    display.add(new Polygon(*pToBorderRectangle));

    criarMundo(display);

    QVector<Ponto> pPontosCamera= pToCamera->getPoints();
    double Wxmin = pPontosCamera[0][0][0];
    double Wymin = pPontosCamera[0][1][0];
    double Wxmax = pPontosCamera[2][0][0];
    double Wymax = pPontosCamera[2][1][0];
    for (const Ponto& p : pPontosCamera) {

        if (p[0][0] < Wxmin) Wxmin = p[0][0];

        if (p[0][0] > Wxmax) Wxmax = p[0][0];

        if (p[1][0] > Wymin) Wymin = p[1][0];

        if (p[1][0] < Wymax) Wymax = p[1][0];

    }
    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform(pToCamera->angleRelativeToX);

    //Normaliza todos os pontos para SCN eu acho
    display.triggerNormalize(Wxmax, Wxmin, Wymin, Wymax); // window

    //Transforma SCN para viewport
    display.triggerViewport(width(), 0, height(), 0);

    //painter.setWindow(-worldX, worldY, this->width(), this->height());

    //display.printAll();
    display.drawAll(painter);
    cout << "Update event\n";
}
MainWindow::~MainWindow()
{
    delete ui;
    delete pToCamera;
    delete pToBorderRectangle;
}

void MainWindow::on_right_clicked()
{
    //botão deve mover camera para direita
    pToCamera->transformObject(10,0,0);
    pToBorderRectangle->transformObject(20,0,0);
    update();
}


void MainWindow::on_down_clicked()
{
    //botão deve mover camera para baixo
    pToCamera->transformObject(0,-10,0);
    pToBorderRectangle->transformObject(0,-20,0);
    update();
}


void MainWindow::on_left_clicked()
{
    //botão deve mover camera para a esquerda
    pToCamera->transformObject(-10,0,0);
    pToBorderRectangle->transformObject(-20,0,0);
    update();
}


void MainWindow::on_up_clicked()
{
    //botão deve mover camera para cima
    pToCamera->transformObject(0,10,0);
    pToBorderRectangle->transformObject(0,20,0);
    update();
}

