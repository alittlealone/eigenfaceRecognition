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

	label = new QLabel();

	connect(open, SIGNAL(clicked()), this, SLOT(setVideoPath()));

	layout = new QVBoxLayout;
	layout->addLayout(upLayout);
	layout->addWidget(label);

	setLayout(layout);
}

VideoPage::~VideoPage()
{
	delete ui;
}

void VideoPage::setVideoPath()
{
	this->videoPath = QFileDialog::getOpenFileName(this, tr("Open Video"),
		"E://", tr("Video Files (*.mkv *.mp4 *.rmvb)"));
	this->label->setText(videoPath);
}
