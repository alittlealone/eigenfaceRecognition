/********************************************************************************
** Form generated from reading UI file 'picturepage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREPAGE_H
#define UI_PICTUREPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PicturePage
{
public:

    void setupUi(QWidget *PicturePage)
    {
        if (PicturePage->objectName().isEmpty())
            PicturePage->setObjectName(QStringLiteral("PicturePage"));
        PicturePage->resize(400, 300);

        retranslateUi(PicturePage);

        QMetaObject::connectSlotsByName(PicturePage);
    } // setupUi

    void retranslateUi(QWidget *PicturePage)
    {
        PicturePage->setWindowTitle(QApplication::translate("PicturePage", "PicturePage", 0));
    } // retranslateUi

};

namespace Ui {
    class PicturePage: public Ui_PicturePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREPAGE_H
