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

    open = new QPushButton(tr("Open"));
    start = new QPushButton(tr("Start"));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(open);
    upLayout->addWidget(start);

    label = new QLabel;
    number_label = "Total number of person in the picture is: ";
    result = new QLabel(number_label);

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

    cv::CascadeClassifier face_cascade("C:\\Users\\Administrator\\Desktop\\haarcascade_frontalface_alt.xml");
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

    faceNumber = faces.size();
    for (int i = 0; i < faceNumber; i++)
    {
        cv::rectangle(image, faces[i], cv::Scalar(255, 0, 255), 1, 8, 0);
    }

    QImage result_img = QImage((uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_RGB888);
    result_img = result_img.scaled(label->width(), label->height(), Qt::KeepAspectRatio, Qt::FastTransformation);
    label->setPixmap(QPixmap::fromImage(result_img));

    number_label.append(QString::number(faceNumber));
    result->setText(number_label);
}
