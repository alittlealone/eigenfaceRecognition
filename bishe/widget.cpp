#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    sysName = new QLabel(tr("Face Recognition System"));
    button_database = new QPushButton(tr("database recognition"));
    button_picture = new QPushButton(tr("picture recognition"));
    button_camera = new QPushButton(tr("camera recognition"));
    button_video = new QPushButton(tr("video recognition"));
    info = new QLabel(tr("Ivy Wang"));

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

Widget::~Widget()
{
    delete ui;
}
