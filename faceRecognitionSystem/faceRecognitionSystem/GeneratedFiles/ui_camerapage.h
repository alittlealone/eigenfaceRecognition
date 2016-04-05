/********************************************************************************
** Form generated from reading UI file 'camerapage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPAGE_H
#define UI_CAMERAPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraPage
{
public:

    void setupUi(QWidget *CameraPage)
    {
        if (CameraPage->objectName().isEmpty())
            CameraPage->setObjectName(QStringLiteral("CameraPage"));
        CameraPage->resize(400, 300);

        retranslateUi(CameraPage);

        QMetaObject::connectSlotsByName(CameraPage);
    } // setupUi

    void retranslateUi(QWidget *CameraPage)
    {
        CameraPage->setWindowTitle(QApplication::translate("CameraPage", "CameraPage", 0));
    } // retranslateUi

};

namespace Ui {
    class CameraPage: public Ui_CameraPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPAGE_H
