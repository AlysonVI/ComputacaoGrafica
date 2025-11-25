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
                                     {-250, -250}, {-250, 250}, {250, 250}, {250, -250}
                                 });

    pToCamera->transformObject(150,250,-300); //Camera
    //pToCamera->rotateCamera(Ponto(150,149,0));
    pToCamera->scaleObject(2,2,0); //Camera
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


    /*
    // Linha clipada 1
    Ponto p11(500,300);
    Ponto p21(-50,-50);
    auto linha1 = clipLine(pToBorderRectangle.getXfromPoints(1), pToBorderRectangle.getXfromPoints(2),
                                            pToBorderRectangle.getYfromPoints(0), pToBorderRectangle.getYfromPoints(1), p11, p21);
                                            // Se substituir pToBorderRectangle por pToCamera, o clipping ocorrera na camera ao inves da borda
    if(linha1)
        display.add(linha1.release());
    */

    castelo1->scaleObject(1.2, 1.2, 0);
    castelo1->rotateObjectX(M_PI);

    castelo2->scaleObject(0.5, 0.5, 0);
    castelo2->transformObject(0, 100, 0);
    castelo2->rotateObjectY(M_PI/2);

    castelo3->rotateObjectX(-M_PI/5);

    // modelos obj
    /*
    ModeloOBJ* modelo1 = new ModeloOBJ("/home/alysonvi/Documentos/UTFPR/Periodo4/ComputacaoGrafica/Projeto CG/objFiles/Lopunny.obj");
    display.add(modelo1);
    modelo1->transformObject(200,450,0);
    modelo1->rotateObjectX(M_PI/2-0.3);
    modelo1->rotateObjectY(M_PI/5);
    modelo1->rotateObjectZ(M_PI);
    modelo1->scaleObject(2.5,2.5,2.5);
    */
    ModeloOBJ* modelo2 = new ModeloOBJ("/home/atosarruda/Documentos/CG/ComputacaoGrafica/objFiles/Vaporeon.obj");
    display.add(modelo2);
    modelo2->transformObject(350,200,0);
    modelo2->rotateObjectX(M_PI/2);
    modelo2->rotateObjectY(-M_PI/2-1);
    modelo2->rotateObjectZ(M_PI-0.3);
    modelo2->scaleObject(2.5,2.5,2.5);

}

void MainWindow::paintEvent(QPaintEvent* event){
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::green);
    DisplayFile display;

    display.add(new Camera(*pToCamera));

    criarMundo(display);


    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform(pToCamera);
    //Aplica a transformação de perspectiva antes de normalizar
    display.triggerPerspective(pToCamera->distance);
    //Normaliza todos os pontos para SCN


    double halfWidth = 500.0;
    double halfHeight = 500.0;
    display.triggerNormalize(halfWidth, -halfWidth, halfHeight, -halfHeight); // window simetrica os valores podem ser fixos

    //Faz o clipping, removendo todos os objetos fora da tela NAO FUNCIONA AINDA, DEVE TER ALGUM ERRINHO
    //display.triggerClipping(Wxmax-50, Wxmin+50, Wymax-50, Wymin+50);

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
}

// "Direita" (Strafe Right)
void MainWindow::on_right_clicked() {
    pToCamera->transformObject(50, 0, 0);
    update();
}

// "Esquerda" (Strafe Left)
void MainWindow::on_left_clicked() {
    pToCamera->transformObject(-50, 0, 0);
    update();
}

// "Cima" (Move Forward)
void MainWindow::on_up_clicked() {
    pToCamera->transformObject(0, 50, 0);
    update();
}

// "Baixo" (Move Backward)
void MainWindow::on_down_clicked() {
    pToCamera->transformObject(0, -50, 0);
    update();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
   indexG = index;
}


void MainWindow::on_XRotate_clicked()
{
    display.getObject(indexG)->rotateObjectX(10);
}


void MainWindow::on_YRotate_clicked()
{
    display.getObject(indexG)->rotateObjectY(10);
}


void MainWindow::on_ZRotate_clicked()
{
    display.getObject(indexG)->rotateObjectZ(10);
}

