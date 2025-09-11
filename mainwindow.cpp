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

    display.add(new Linha("cima", Ponto(0,0), Ponto(100,0)));
    display.add(new Linha("direita", Ponto(100,0), Ponto(100,100)));
    display.add(new Linha("baixo", Ponto(100,100), Ponto(0,100)));
    display.add(new Linha("esquerda",  Ponto(0,100), Ponto(0,0)));

    display.add(new Polygon("rect", QVector<Ponto>{
            {170, 0}, {220, 100}, {120, 100}
        }));

    display.getObject(4)->transladar(50, 100);


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
