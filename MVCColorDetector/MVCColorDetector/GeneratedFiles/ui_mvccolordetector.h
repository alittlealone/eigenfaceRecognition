/********************************************************************************
** Form generated from reading UI file 'mvccolordetector.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MVCCOLORDETECTOR_H
#define UI_MVCCOLORDETECTOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MVCColorDetectorClass
{
public:
    QAction *actionOpen_Image;
    QAction *actionChoose_Color;
    QAction *actionProcess;
    QAction *actionQuit;
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton_openImage;
    QPushButton *pushButton_color;
    QSlider *verticalSlider_Threshold;
    QLabel *label_2;
    QPushButton *pushButton_process;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MVCColorDetectorClass)
    {
        if (MVCColorDetectorClass->objectName().isEmpty())
            MVCColorDetectorClass->setObjectName(QStringLiteral("MVCColorDetectorClass"));
        MVCColorDetectorClass->resize(600, 400);
        actionOpen_Image = new QAction(MVCColorDetectorClass);
        actionOpen_Image->setObjectName(QStringLiteral("actionOpen_Image"));
        actionChoose_Color = new QAction(MVCColorDetectorClass);
        actionChoose_Color->setObjectName(QStringLiteral("actionChoose_Color"));
        actionProcess = new QAction(MVCColorDetectorClass);
        actionProcess->setObjectName(QStringLiteral("actionProcess"));
        actionQuit = new QAction(MVCColorDetectorClass);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MVCColorDetectorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 20, 431, 311));
        pushButton_openImage = new QPushButton(centralWidget);
        pushButton_openImage->setObjectName(QStringLiteral("pushButton_openImage"));
        pushButton_openImage->setGeometry(QRect(20, 20, 81, 23));
        pushButton_color = new QPushButton(centralWidget);
        pushButton_color->setObjectName(QStringLiteral("pushButton_color"));
        pushButton_color->setGeometry(QRect(20, 60, 81, 23));
        verticalSlider_Threshold = new QSlider(centralWidget);
        verticalSlider_Threshold->setObjectName(QStringLiteral("verticalSlider_Threshold"));
        verticalSlider_Threshold->setGeometry(QRect(50, 100, 22, 121));
        verticalSlider_Threshold->setOrientation(Qt::Vertical);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 240, 81, 31));
        pushButton_process = new QPushButton(centralWidget);
        pushButton_process->setObjectName(QStringLiteral("pushButton_process"));
        pushButton_process->setGeometry(QRect(30, 280, 75, 23));
        MVCColorDetectorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MVCColorDetectorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MVCColorDetectorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MVCColorDetectorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MVCColorDetectorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MVCColorDetectorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MVCColorDetectorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen_Image);
        menuFile->addAction(actionChoose_Color);
        menuFile->addAction(actionProcess);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MVCColorDetectorClass);

        QMetaObject::connectSlotsByName(MVCColorDetectorClass);
    } // setupUi

    void retranslateUi(QMainWindow *MVCColorDetectorClass)
    {
        MVCColorDetectorClass->setWindowTitle(QApplication::translate("MVCColorDetectorClass", "MVCColorDetector", 0));
        actionOpen_Image->setText(QApplication::translate("MVCColorDetectorClass", "Open Image", 0));
        actionChoose_Color->setText(QApplication::translate("MVCColorDetectorClass", "Choose Color", 0));
        actionProcess->setText(QApplication::translate("MVCColorDetectorClass", "Process", 0));
        actionQuit->setText(QApplication::translate("MVCColorDetectorClass", "Quit", 0));
        label->setText(QString());
        pushButton_openImage->setText(QApplication::translate("MVCColorDetectorClass", "Open Image", 0));
        pushButton_color->setText(QApplication::translate("MVCColorDetectorClass", "Select Color", 0));
        label_2->setText(QApplication::translate("MVCColorDetectorClass", "Threshold: 0", 0));
        pushButton_process->setText(QApplication::translate("MVCColorDetectorClass", "Process", 0));
        menuFile->setTitle(QApplication::translate("MVCColorDetectorClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MVCColorDetectorClass: public Ui_MVCColorDetectorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MVCCOLORDETECTOR_H
