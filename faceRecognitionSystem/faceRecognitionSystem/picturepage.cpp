#include "picturepage.h"

PicturePage::PicturePage(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::PicturePage();
	ui->setupUi(this);

	open = new QPushButton(tr("Open"));

	upLayout = new QHBoxLayout;
	upLayout->addWidget(open);
	upLayout->addStretch();

	label = new QLabel(tr("picture goes here..."));
	result = new QLabel(tr("Total number of person in the picture is: "));

	layout = new QVBoxLayout;
	layout->addLayout(upLayout);
	layout->addWidget(label);
	layout->addWidget(result);

	setLayout(layout);
}

PicturePage::~PicturePage()
{
	delete ui;
}
