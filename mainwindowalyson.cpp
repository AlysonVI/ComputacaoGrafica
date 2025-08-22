#include "mainwindowalyson.h"
#include "ui_mainwindowalyson.h"

MainWindowAlyson::MainWindowAlyson(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowAlyson)
{
    ui->setupUi(this);
}

MainWindowAlyson::~MainWindowAlyson()
{
    delete ui;
}
