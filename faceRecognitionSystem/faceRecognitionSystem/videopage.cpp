#include "videopage.h"
#include "ui_videopage.h"

VideoPage::VideoPage(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::VideoPage();
	ui->setupUi(this);

	open = new QPushButton(tr("Open"));

	upLayout = new QHBoxLayout;
	upLayout->addWidget(open);
	upLayout->addStretch();

	label = new QLabel(tr("video goes here..."));

	layout = new QVBoxLayout;
	layout->addLayout(upLayout);
	layout->addWidget(label);

	setLayout(layout);
}

VideoPage::~VideoPage()
{
	delete ui;
}

