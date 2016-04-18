#include "picturepage.h"
#include "ui_picturepage.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFileDialog>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

PicturePage::PicturePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicturePage)
{
    ui->setupUi(this);

    setTrainPath = new QPushButton(tr("Set path"));
    open = new QPushButton(tr("Open"));
    start = new QPushButton(tr("Start"));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(setTrainPath);
    upLayout->addWidget(open);
    upLayout->addWidget(start);

    label = new QLabel;
    number_label = "Total number of person in the picture is: ";
    result = new QLabel(number_label);

    connect(setTrainPath, SIGNAL(clicked()), this, SLOT(setDatabasePath()));
    connect(open, SIGNAL(clicked()), this, SLOT(showImage()));
    connect(start, SIGNAL(clicked()), this, SLOT(recognize()));

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

void PicturePage::labels()
{
    std::vector<int> labels;
    ////////below really needs modify!!!!!!!
    labels.push_back(1);
    for(int i = 1; i < 4; i++)
        labels.push_back(2);
    this->labelVector = labels;
}

void PicturePage::setDatabasePath()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Set Path"));
    pcaPictureModel = new pca(path.toStdString());
    this->labels();
    pcaPictureModel->setLabel(labelVector);

    //train
    pcaPictureModel->train();
    QMessageBox::information(this, tr("finish"), tr("Training finish!"));
}

void PicturePage::showImage()
{
    number_label = "Total number of person in the picture is: ";
    result->setText(number_label);

    imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                            "E://图片", tr("Image Files (*.png *.jpg *.bmp *.tif)"));

    if(imagePath.isEmpty())
    {
        return;
    }
    else
    {
        img=new QImage;

        if(!(img->load(imagePath)))
        {
            QMessageBox::information(this, tr("error"), tr("Failed to open this image!"));
            delete img;
            return;
        }
//        QImage result = image.scaled(800, 600).scaled(120, 180, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//        img = & img->scaled(label->width(), label->height());

        *img = img->scaled(label->width(), label->height(), Qt::KeepAspectRatio, Qt::FastTransformation);

        this->label->setPixmap(QPixmap::fromImage(*img));
//        label->resize(label->width(), label->height());
    }
}

void PicturePage::recognize()
{
    cv::Mat image = cv::imread(imagePath.toStdString(), CV_LOAD_IMAGE_COLOR);

//    cv::resize(image, image, cv::Size(label->width(), label->height()));
//    cv::cvtColor(image,image,CV_BGR2RGB);

    cv::Mat original = image.clone();
    cv::Mat gray;
    cvtColor(original, gray, CV_BGR2GRAY);

    cv::CascadeClassifier face_cascade("C:\\Users\\Administrator\\Desktop\\haarcascade_frontalface_alt.xml");
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    int im_width = pcaPictureModel->getOriginalData()[0].cols;
    int im_height = pcaPictureModel->getOriginalData()[0].rows;

    //predict
    faceNumber = faces.size();
    for (int i = 0; i < faceNumber; i++)
    {
//        cv::rectangle(image, faces[i], cv::Scalar(255, 0, 255), 1, 8, 0);
        cv::Rect face_i = faces[i];
        cv::rectangle(image, face_i, cv::Scalar(255, 0, 255), 1, 8, 0);

        cv::Mat face = gray(face_i);
        cv::Mat face_resized;
        cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

        pcaPictureModel->setTestData(face_resized);
        pcaPictureModel->predict();
        int prediction = pcaPictureModel->getPredictedLabel();

        std:string box_text = format("Prediction = %d", prediction);

        int pos_x = std::max(face_i.tl().x - 10, 0);
        int pos_y = std::max(face_i.tl().y - 10, 0);

        putText(image, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);
    }

    QImage result_img = QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    result_img = result_img.scaled(label->width(), label->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    label->setPixmap(QPixmap::fromImage(result_img));

    number_label.append(QString::number(faceNumber));
    result->setText(number_label);
}
