#include "mainwidget.h"

mainWidget::mainWidget(QWidget *parent)
	: QWidget(parent)
{
	ui->setupUi(this);

	sysName = new QLabel(QStringLiteral("人脸识别系统"));
	button_database = new QPushButton(QStringLiteral("数据库图像人脸识别"));
	button_picture = new QPushButton(QStringLiteral("图片图像人脸识别"));
	button_camera = new QPushButton(QStringLiteral("摄像头实时人脸识别"));
	button_video = new QPushButton(QStringLiteral("视频实时人脸识别"));
	info = new QLabel(QStringLiteral("王子康"));

	buttonGroup = new QButtonGroup;
	buttonGroup->addButton(button_database, 0);
	buttonGroup->addButton(button_picture, 1);
	buttonGroup->addButton(button_camera, 2);
	buttonGroup->addButton(button_video, 3);

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget(sysName);
	leftLayout->addWidget(button_database);
	leftLayout->addWidget(button_picture);
	leftLayout->addWidget(button_camera);
	leftLayout->addWidget(button_video);
	leftLayout->addWidget(info);

	databasePage = new DatabasePage();
	picturePage = new PicturePage();
	cameraPage = new CameraPage();
	videoPage = new VideoPage();

	stackedLayout = new QStackedLayout;
	stackedLayout->addWidget(databasePage);
	stackedLayout->addWidget(picturePage);
	stackedLayout->addWidget(cameraPage);
	stackedLayout->addWidget(videoPage);

	connect(buttonGroup, SIGNAL(buttonClicked(int)), stackedLayout, SLOT(setCurrentIndex(int)));

	mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(stackedLayout);
	mainLayout->setMargin(20);
	mainLayout->setSpacing(5);

	setLayout(mainLayout);
}

mainWidget::~mainWidget()
{
	delete ui;
}
