#include "mainwindowalyson.h"
#include "ui_mainwindowalyson.h"
#include "QPainter"
#include "iostream"
int worldX = 400;
int worldY = 400;

MainWindowAlyson::MainWindowAlyson(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowAlyson)
{
    setFixedSize(worldX, worldY);
    setStyleSheet("background-color: #f3cfc6;");

    QPainter painter(this);

    painter.setViewport(0, 0, this->width(), this->height());
    painter.setWindow(-worldX / 2, -worldY / 2, worldX, worldY);



    ui->setupUi(this);


}

MainWindowAlyson::~MainWindowAlyson()
{
    delete ui;
}
