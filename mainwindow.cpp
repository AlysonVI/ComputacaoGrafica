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

    pToCamera->transformObject(200,250,200); //Camera
    //pToCamera->rotateCamera(Ponto(150,149,0));
    pToCamera->scaleObject(2,2,1); //Camera

    this->display.add(new Camera(*pToCamera));

    criarMundo(this->display);
}

void MainWindow::criarMundo(DisplayFile& display) {
    // modelo obj
    /*
    ModeloOBJ* modelo1 = new ModeloOBJ("/home/alysonvi/Documentos/UTFPR/Periodo4/ComputacaoGrafica/ProjetoCG/objFiles/Lopunny.obj");
    display.add(modelo1);
    modelo1->transformObject(200,450,0);
    modelo1->rotateObjectX(M_PI/2-0.3);
    modelo1->rotateObjectY(M_PI/5);
    modelo1->rotateObjectZ(M_PI);
    */
    Castelo* castelo1 = new Castelo(Ponto(200,200));
    Castelo* castelo2 = new Castelo(Ponto(70,250));
    Castelo* castelo3 = new Castelo(Ponto(300,400));
    Curva* curva = new Curva("curva", Ponto(200,100,-100), Ponto(250,50,-150), Ponto(250,300,-250), 5);

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

    castelo1->scaleObject(1.2, 1.2, 1.0);
    castelo1->rotateObjectX(M_PI);

    castelo2->scaleObject(0.5, 0.5, 1.0);
    castelo2->transformObject(0, 100, 0);
    castelo2->rotateObjectY(M_PI/2);

    castelo3->rotateObjectX(-M_PI/5);

    // modelo obj
    ModeloOBJ* modelo2 = new ModeloOBJ("/Qt/ComputacaoGrafica/objFiles/Vaporeon.obj");
    display.add(modelo2);
    modelo2->transformObject(150,250,-200);
    modelo2->rotateObjectX(M_PI/2);
    modelo2->rotateObjectY(M_PI/4);
    modelo2->rotateObjectZ(M_PI-0.3);
    //modelo2->scaleObject(2.5,2.5,2.5);

}

void MainWindow::paintEvent(QPaintEvent* event){
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::green);


    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform(pToCamera);
    //Aplica a transformação de perspectiva antes de normalizar

    //Faz o clipping no eixo Z antes de fazer a perspectiva, para o eixo Z não ser desprezado
    display.triggerZClipping();

    display.triggerPerspective(pToCamera->distance);
    //Normaliza todos os pontos para SCN


    double halfWidth = 500.0;
    double halfHeight = 500.0;
    display.triggerNormalize(-halfWidth, halfWidth, -halfHeight, halfHeight); // window simetrica os valores podem ser fixos

    //Faz o clipping, removendo todas as linhas fora da tela
    double borda = 0.4;
    display.triggerXYClipping(1-borda,-1+borda,1-borda,-1+borda);

    //Transforma SCN para viewport
    display.triggerViewport(width(), 0, height(), 0);

    //painter.setWindow(-worldX, worldY, this->width(), this->height());

    //display.printAll();
    display.drawAll(painter);



    // Representação visual da borda, para fins de debbug
    viewportX = this->width();
    viewportY = this->height();
    double borderSize = viewportX*borda/2;
    QPointF p1(borderSize, borderSize);
    QPointF p2(borderSize, viewportY-borderSize);
    QPointF p3(viewportX-borderSize, viewportY-borderSize);
    QPointF p4(viewportX-borderSize, borderSize);

    painter.setPen(Qt::red);
    painter.drawLine(p1,p2);
    painter.drawLine(p2,p3);
    painter.drawLine(p3,p4);
    painter.drawLine(p4,p1);


}
MainWindow::~MainWindow()
{
    delete ui;
    delete pToCamera;
}

// "Direita" (Strafe Right)
void MainWindow::on_right_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(50, 0, 0);
    else
        display.getObject(indexG)->transformObject(50, 0, 0);
    update();
}

// "Esquerda" (Strafe Left)
void MainWindow::on_left_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(-50, 0, 0);
    else
        display.getObject(indexG)->transformObject(-50, 0, 0);
    update();
}

// "Cima" (Move Forward)
void MainWindow::on_up_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(0, 50, 0);
    else
        display.getObject(indexG)->transformObject(0, 50, 0);
    update();
}

// "Baixo" (Move Backward)
void MainWindow::on_down_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(0, -50, 0);
    else
        display.getObject(indexG)->transformObject(0, -50, 0);
    update();
}

void MainWindow::on_YRotate_clicked()
{
    if(indexG != 0){
        display.getObject(indexG)->rotateObjectY(1);
    }
    else
    {
        //pToCamera->rotateCamera(Ponto(100,100,100));
    }
    update();
}


void MainWindow::on_ZRotate_clicked()
{
    if(indexG != 0){
        display.getObject(indexG)->rotateObjectZ(1);
    }
    else
    {
        //pToCamera->rotateCamera(Ponto(100,100,100));
    }
    update();
}


void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if( arg1 <= display.objects.size()){
        indexG = arg1;
    }
    else
    {
        indexG = 0;
    }

}


void MainWindow::on_zGoFront_clicked()
{
    if(indexG == 0)
        pToCamera->transformObject(0, 0, -50);
    else
        display.getObject(indexG)->transformObject(0, 0, -50);
    update();
}


void MainWindow::on_zGoBack_clicked()
{
    if(indexG == 0)
        pToCamera->transformObject(0, 0, 50);
    else
        display.getObject(indexG)->transformObject(0, 0, 50);
    update();
}


void MainWindow::on_xRotate_clicked()
{
    if(indexG != 0){
        display.getObject(indexG)->rotateObjectX(1);
    }
    else
    {
        //pToCamera->rotateCamera(Ponto(100,100,100));
    }
    update();
}

