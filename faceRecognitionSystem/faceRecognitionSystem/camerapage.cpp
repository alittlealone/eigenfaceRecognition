#include "camerapage.h"
#include "ui_camerapage.h"

CameraPage::CameraPage(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CameraPage();
	ui->setupUi(this);
}

CameraPage::~CameraPage()
{
	delete ui;
}

