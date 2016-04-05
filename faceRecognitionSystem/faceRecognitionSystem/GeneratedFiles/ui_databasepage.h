/********************************************************************************
** Form generated from reading UI file 'databasepage.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEPAGE_H
#define UI_DATABASEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabasePage
{
public:

    void setupUi(QWidget *DatabasePage)
    {
        if (DatabasePage->objectName().isEmpty())
            DatabasePage->setObjectName(QStringLiteral("DatabasePage"));
        DatabasePage->resize(400, 300);

        retranslateUi(DatabasePage);

        QMetaObject::connectSlotsByName(DatabasePage);
    } // setupUi

    void retranslateUi(QWidget *DatabasePage)
    {
        DatabasePage->setWindowTitle(QApplication::translate("DatabasePage", "DatabasePage", 0));
    } // retranslateUi

};

namespace Ui {
    class DatabasePage: public Ui_DatabasePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEPAGE_H
