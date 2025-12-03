#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Ponto.h"
#include "Linha.h"
#include "Polygon.h"
#include <QPainter>
#include <math.h>
#include "Castelo.h"
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
    Castelo* castelo1 = new Castelo(Ponto(200,200));
    castelo1->scaleObject(1.2, 1.2, 1.2);
    castelo1->rotateObjectX(M_PI);
    castelo1->transformObject(100, 0, -200);

    Castelo* castelo2 = new Castelo(Ponto(70,250));
    castelo2->scaleObject(0.5, 0.5, 1.0);
    castelo2->transformObject(0, 100, 0);
    castelo2->rotateObjectY(M_PI/2);

    Castelo* castelo3 = new Castelo(Ponto(300,400));
    castelo3->rotateObjectZ(-M_PI/5);
    castelo3->rotateObjectX(M_PI/5);
    castelo3->transformObject(-100, -100, 100);

    display.add(castelo1);
    display.add(castelo2);
    display.add(castelo3);

    Curva* curva = new Curva("curva", Ponto(200,100,-100), Ponto(250,50,-150), Ponto(250,300,-250), 5);
    curva->rotateObjectY(M_PI/2);
    display.add(curva);


    // Modelos obj dos pokemons que estão na pasta junto com o projeto, comentei o Lopunny para economizar processamento
    /*
    ModeloOBJ* modeloLopunny = new ModeloOBJ("/home/alysonvi/Documentos/UTFPR/Periodo4/ComputacaoGrafica/ProjetoCG/objFiles/Lopunny.obj");
    modeloLopunny->transformObject(200,350,-200);
    modeloLopunny->rotateObjectX(M_PI/2-0.3);
    modeloLopunny->rotateObjectY(M_PI/5);
    modeloLopunny->rotateObjectZ(M_PI);
    modeloLopunny->scaleObject(0.6,0.6,0.6);

    display.add(modeloLopunny);
    */

    ModeloOBJ* modeloVaporeon = new ModeloOBJ("/home/alysonvi/Documentos/UTFPR/Periodo4/ComputacaoGrafica/ProjetoCG/objFiles/Vaporeon.obj");
    modeloVaporeon->transformObject(50,250,-100);
    modeloVaporeon->rotateObjectX(M_PI/2);
    modeloVaporeon->rotateObjectY(M_PI/4);
    modeloVaporeon->rotateObjectZ(M_PI-0.3);

    display.add(modeloVaporeon);
}

void MainWindow::paintEvent(QPaintEvent* event){
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);
    painter.setPen(Qt::green);

    //Matriz global(centraliza e rotaciona o mundo)
    display.applyGlobalTransform(pToCamera);

    //Faz o clipping no eixo Z antes de fazer a perspectiva, para o eixo Z não ser desprezado
    display.triggerZClipping();

    //Aplica a transformação de perspectiva antes de normalizar
    display.triggerPerspective(pToCamera->distance);

    double halfWidth = 500.0;
    double halfHeight = 500.0;
    display.triggerNormalize(-halfWidth, halfWidth, -halfHeight, halfHeight); // window simetrica os valores podem ser fixos

    //Faz o clipping, removendo todas as linhas fora da tela
    double borda = 0.4;
    display.triggerXYClipping(1-borda,-1+borda,1-borda,-1+borda);

    //Transforma SCN para viewport
    display.triggerViewport(width(), 0, height(), 0);

    //display.printAll();
    display.drawAll(painter);

    // Representação visual da borda (retangulo vermelho)
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

// Move objeto selecionado para a direita
void MainWindow::on_right_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(50, 0, 0);
    else
        display.getObject(indexG)->transformObject(50, 0, 0);
    update();
}

// Move objeto selecionado para a esquerda
void MainWindow::on_left_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(-50, 0, 0);
    else
        display.getObject(indexG)->transformObject(-50, 0, 0);
    update();
}

// Move objeto selecionado para cima
void MainWindow::on_up_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(0, 50, 0);
    else
        display.getObject(indexG)->transformObject(0, 50, 0);
    update();
}

// Move objeto selecionado para baixo
void MainWindow::on_down_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(0, -50, 0);
    else
        display.getObject(indexG)->transformObject(0, -50, 0);
    update();
}

// Rotaciona objeto selecionado em relação ao eixo X
void MainWindow::on_xRotate_clicked() {
    if(indexG != 0)
        display.getObject(indexG)->rotateObjectX(1);
    else {
        Ponto newVpn = pToCamera->getVectorVpn();
        newVpn.rotatePointX(1);
        pToCamera->setVectorVpn(newVpn);
    }
    update();
}

// Rotaciona objeto selecionado em relação ao eixo Y
void MainWindow::on_YRotate_clicked() {
    if(indexG != 0)
        display.getObject(indexG)->rotateObjectY(1);
    else {
        Ponto newVpn = pToCamera->getVectorVpn();
        newVpn.rotatePointY(1);
        pToCamera->setVectorVpn(newVpn);
    }
    update();
}

// Rotaciona objeto selecionado em relação ao eixo Z
void MainWindow::on_ZRotate_clicked() {
    if(indexG != 0)
        display.getObject(indexG)->rotateObjectZ(1);
    else {
        Ponto newVpn = pToCamera->getVectorVpn();
        newVpn.rotatePointZ(1);
        pToCamera->setVectorVpn(newVpn);
    }
    update();
}

// Lógica na Spinbox para mudar o valor
void MainWindow::on_spinBox_valueChanged(int arg1) {
    if(arg1 <= display.objects.size())
        indexG = arg1;
    else
        indexG = 0;
}

// Move objeto selecionado para frente
void MainWindow::on_zGoFront_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(0, 0, -50);
    else
        display.getObject(indexG)->transformObject(0, 0, -50);
    update();
}

// Move objeto selecionado para trás
void MainWindow::on_zGoBack_clicked() {
    if(indexG == 0)
        pToCamera->transformObject(0, 0, 50);
    else
        display.getObject(indexG)->transformObject(0, 0, 50);
    update();
}
