/********************************************************************************
** Form generated from reading UI file 'mainwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWidgetClass
{
public:

    void setupUi(QWidget *mainWidgetClass)
    {
        if (mainWidgetClass->objectName().isEmpty())
            mainWidgetClass->setObjectName(QStringLiteral("mainWidgetClass"));
        mainWidgetClass->resize(600, 400);

        retranslateUi(mainWidgetClass);

        QMetaObject::connectSlotsByName(mainWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *mainWidgetClass)
    {
        mainWidgetClass->setWindowTitle(QApplication::translate("mainWidgetClass", "mainWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class mainWidgetClass: public Ui_mainWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H
