#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DisplayFile.h"
#include "Camera.h"
#include "Polygon.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DisplayFile display;
    int indexG= 0;
    Camera* pToCamera;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void casteljau(DisplayFile& display, Ponto &p0, Ponto &p1, Ponto &p2, int n);
protected:
    void paintEvent(QPaintEvent* event) override;
private slots:
    void on_right_clicked();

    void on_down_clicked();

    void on_left_clicked();

    void on_up_clicked();

    void on_YRotate_clicked();

    void on_ZRotate_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_zGoFront_clicked();

    void on_zGoBack_clicked();

    void on_xRotate_clicked();

private:
    int viewportX;
    int viewportY;


    void criarMundo(DisplayFile& display);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
