#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DisplayFile.h"
#include "Camera.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DisplayFile display;
public:
    Camera* pToCamera;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    int worldX;
    int worldY;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
