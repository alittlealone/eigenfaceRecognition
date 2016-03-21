#include "database.h"
#include "ui_database.h"

database::database(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
}

database::~database()
{
    delete ui;
}
