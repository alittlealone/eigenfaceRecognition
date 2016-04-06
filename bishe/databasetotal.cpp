#include "databasetotal.h"
#include "ui_databasetotal.h"

databaseTotal::databaseTotal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::databaseTotal)
{
    ui->setupUi(this);
}

databaseTotal::~databaseTotal()
{
    delete ui;
}
