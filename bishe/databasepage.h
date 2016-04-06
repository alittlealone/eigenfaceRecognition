#ifndef DATABASEPAGE_H
#define DATABASEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "databasesingle.h"
#include "databasetotal.h"

namespace Ui {
class DatabasePage;
}

class DatabasePage : public QWidget
{
    Q_OBJECT

public:
    explicit DatabasePage(QWidget *parent = 0);
    ~DatabasePage();

private:
    Ui::DatabasePage *ui;

    QLabel *label_choose;
    QComboBox *comboBox;
    QHBoxLayout *upLayout;
    QVBoxLayout *layout;
    QTabWidget *tabWidget;

    databaseSingle *singleTab;
    databaseTotal *totalTab;


};

#endif // DATABASEPAGE_H
