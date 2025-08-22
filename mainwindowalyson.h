#ifndef MAINWINDOWALYSON_H
#define MAINWINDOWALYSON_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowAlyson;
}
QT_END_NAMESPACE

class MainWindowAlyson : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowAlyson(QWidget *parent = nullptr);
    ~MainWindowAlyson();

private:
    Ui::MainWindowAlyson *ui;
};
#endif // MAINWINDOWALYSON_H
