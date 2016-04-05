#include "camerapage.h"
#include "ui_camerapage.h"

CameraPage::CameraPage(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::CameraPage();
	ui->setupUi(this);

	open = new QPushButton(tr("open"));
	close = new QPushButton(tr("close"));
	upLayout = new QHBoxLayout;
	upLayout->addWidget(open);
	upLayout->addWidget(close);

	label = new QLabel(tr("video goes here..."));

	layout = new QVBoxLayout;
	layout->addLayout(upLayout);
	layout->addWidget(label);

	setLayout(layout);
}

CameraPage::~CameraPage()
{
	delete ui;
}

