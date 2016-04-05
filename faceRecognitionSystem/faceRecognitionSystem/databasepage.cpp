#include "databasepage.h"
#include "ui_databasepage.h"

DatabasePage::DatabasePage(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::DatabasePage();
	ui->setupUi(this);
}

DatabasePage::~DatabasePage()
{
	delete ui;
}

