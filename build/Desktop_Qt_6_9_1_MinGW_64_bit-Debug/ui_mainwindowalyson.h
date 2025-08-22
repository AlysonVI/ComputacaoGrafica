/********************************************************************************
** Form generated from reading UI file 'mainwindowalyson.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWALYSON_H
#define UI_MAINWINDOWALYSON_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowAlyson
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuAAAA;
    QMenu *menuBBBB;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowAlyson)
    {
        if (MainWindowAlyson->objectName().isEmpty())
            MainWindowAlyson->setObjectName("MainWindowAlyson");
        MainWindowAlyson->resize(800, 600);
        centralwidget = new QWidget(MainWindowAlyson);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(310, 230, 161, 71));
        MainWindowAlyson->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowAlyson);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuAAAA = new QMenu(menubar);
        menuAAAA->setObjectName("menuAAAA");
        menuBBBB = new QMenu(menubar);
        menuBBBB->setObjectName("menuBBBB");
        MainWindowAlyson->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowAlyson);
        statusbar->setObjectName("statusbar");
        MainWindowAlyson->setStatusBar(statusbar);

        menubar->addAction(menuAAAA->menuAction());
        menubar->addAction(menuBBBB->menuAction());

        retranslateUi(MainWindowAlyson);
        QObject::connect(pushButton, &QPushButton::clicked, MainWindowAlyson, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindowAlyson);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowAlyson)
    {
        MainWindowAlyson->setWindowTitle(QCoreApplication::translate("MainWindowAlyson", "MainWindowAlyson", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindowAlyson", "Sair", nullptr));
        menuAAAA->setTitle(QCoreApplication::translate("MainWindowAlyson", "AAAA", nullptr));
        menuBBBB->setTitle(QCoreApplication::translate("MainWindowAlyson", "BBBB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowAlyson: public Ui_MainWindowAlyson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWALYSON_H
