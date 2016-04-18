#include "videopage.h"
#include "ui_videopage.h"

#include <QImage>
#include <QMessageBox>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>
#include <string>

VideoPage::VideoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPage)
{
    ui->setupUi(this);

    setDatabase = new QPushButton(tr("Choose database"));
    train = new QPushButton(tr("train"));
    open = new QPushButton(tr("Open"));
    pause = new QPushButton(tr("Pause"));
//    close = new QPushButton(tr("Close"));

    connect(setDatabase, SIGNAL(clicked()), this, SLOT(setDatabasePath()));
    connect(setDatabase, SIGNAL(clicked()), this, SLOT(labels()));
    connect(train, SIGNAL(clicked()), this, SLOT(trainModel()));
    connect(open, SIGNAL(clicked()), this, SLOT(playVideo()));
    connect(pause, SIGNAL(clicked()), this, SLOT(pauseVideo()));
//    connect(close, SIGNAL(clicked()), this, SLOT(closeVideo()));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(setDatabase);
    upLayout->addWidget(train);
    upLayout->addWidget(open);
    upLayout->addWidget(pause);
//    upLayout->addWidget(close);
    upLayout->addStretch();

    label = new QLabel();

    layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addWidget(label);

    setLayout(layout);
}

VideoPage::~VideoPage()
{
    timer->stop();
    delete ui;
}

void VideoPage::setDatabasePath()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Set Path"));
    pcaVideoModel = new pca(path.toStdString());
}

void VideoPage::labels()
{
    std::vector<int> labels;
    ////////below really need modify!!!!!!!
    for(int i = 0; i < 3; i++)
        labels.push_back(1);
    this->labelVector = labels;
}

void VideoPage::trainModel()
{
    pcaVideoModel->setLabel(labelVector);
    pcaVideoModel->train();
    QMessageBox::information(this, tr("finish"), tr("Training finish!"));

    im_width = pcaVideoModel->getOriginalData()[0].cols;
    im_height = pcaVideoModel->getOriginalData()[0].rows;
}

void VideoPage::playVideo()
{
    isPause = false;
    this->videoPath = QFileDialog::getOpenFileName(this, tr("Open Video"),
                                            "F://", tr("Video Files (*.mkv *.mp4 *.rmvb *.flv)"));
    capture = new cv::VideoCapture(videoPath.toStdString());
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame()));
    timer->start(30);
}

void VideoPage::displayFrame()
{
    if(isPause) {
        timer->stop();
    }

    cv::CascadeClassifier face_cascade("C:\\Users\\Administrator\\Desktop\\haarcascade_frontalface_alt.xml");

    *capture >> frame;

    if (frame.cols == 0 && !isPause) {
        QMessageBox::information(this, tr("error"), tr("error!"));
    }

    cv::resize(frame, frame, cv::Size(label->width(), label->height()));
    cv::cvtColor(frame,frame,CV_BGR2RGB);

    cv::Mat original = frame.clone();
    cv::Mat gray;
    cvtColor(original, gray, CV_BGR2GRAY);

    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    for (int i = 0; i < faces.size(); i++) {
        cv::Rect face_i = faces[i];
        cv::rectangle(frame, face_i, cv::Scalar(255, 0, 255), 1, 8, 0);

        cv::Mat face = gray(face_i);
        cv::Mat face_resized;
        cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

        pcaVideoModel->setTestData(face_resized);
        pcaVideoModel->predict();
        int prediction = pcaVideoModel->getPredictedLabel();

        std:string box_text = format("Prediction = %d", prediction);

        int pos_x = std::max(face_i.tl().x - 10, 0);
        int pos_y = std::max(face_i.tl().y - 10, 0);

        putText(frame, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);
    }

    QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(img);

    label->setPixmap(pix);

}

void VideoPage::pauseVideo()
{
    isPause = true;
}

