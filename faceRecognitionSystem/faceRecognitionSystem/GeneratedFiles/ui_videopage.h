/********************************************************************************
** Form generated from reading UI file 'videopage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPAGE_H
#define UI_VIDEOPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPage
{
public:

    void setupUi(QWidget *VideoPage)
    {
        if (VideoPage->objectName().isEmpty())
            VideoPage->setObjectName(QStringLiteral("VideoPage"));
        VideoPage->resize(400, 300);

        retranslateUi(VideoPage);

        QMetaObject::connectSlotsByName(VideoPage);
    } // setupUi

    void retranslateUi(QWidget *VideoPage)
    {
        VideoPage->setWindowTitle(QApplication::translate("VideoPage", "VideoPage", 0));
    } // retranslateUi

};

namespace Ui {
    class VideoPage: public Ui_VideoPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPAGE_H
