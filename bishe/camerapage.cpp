#include "camerapage.h"
#include "ui_camerapage.h"

#include <QTimer>
#include <QMessageBox>

CameraPage::CameraPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraPage)
{
    ui->setupUi(this);

    open = new QPushButton(tr("open"));
    close = new QPushButton(tr("close"));
    upLayout = new QHBoxLayout;
    upLayout->addWidget(open);
    upLayout->addWidget(close);

    connect(open, SIGNAL(clicked()), this, SLOT(playVideo()));

    label = new QLabel();

    layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addWidget(label);

    setLayout(layout);
}

CameraPage::~CameraPage()
{
    timer->stop();
    cvReleaseCapture(&capture);
    delete ui;
}

void CameraPage::playVideo()
{
//    capture = new cv::VideoCapture(0);
    capture = cvCaptureFromCAM(0);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame()));
    timer->start(40);
}

void CameraPage::displayFrame()
{
//    *capture >> frame;
    frame = cvQueryFrame(capture);

    if (frame.cols == 0) {
         QMessageBox::information(this, tr("error"), tr("error!"));
    }

    cv::resize(frame, frame, cv::Size(label->width(), label->height()));
    cv::cvtColor(frame,frame,CV_BGR2RGB);
    QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(img);
    label->setPixmap(pix);
}
