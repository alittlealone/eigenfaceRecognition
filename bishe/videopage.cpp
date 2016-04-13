#include "videopage.h"
#include "ui_videopage.h"

#include <QImage>
#include <QMessageBox>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>

VideoPage::VideoPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPage)
{
    ui->setupUi(this);

    open = new QPushButton(tr("Open"));

    connect(open, SIGNAL(clicked()), this, SLOT(playVideo()));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(open);
    upLayout->addStretch();

    label = new QLabel();

//    cv::VideoCapture capture("F:/Apple Steve Jobs The Crazy Ones - NEVER BEFORE AIRED 1997 - (Original Post).mp4");
//    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame())); // connect the timer to the widget and to the method that will execute after every refresh
//    timer->start(40); // set the time of refreshment and start the timer

    layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addWidget(label);

    setLayout(layout);
}

VideoPage::~VideoPage()
{
    delete ui;
}

void VideoPage::playVideo()
{
    this->videoPath = QFileDialog::getOpenFileName(this, tr("Open Video"),
                                            "F://", tr("Video Files (*.mkv *.mp4 *.rmvb)"));
    capture = new cv::VideoCapture(videoPath.toStdString());
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(displayFrame())); // connect the timer to the widget and to the method that will execute after every refresh
    timer->start(40); // set the time of refreshment and start the timer
}

void VideoPage::displayFrame()
{
    // read one frame into frame
    *capture >> frame;

    if (frame.cols == 0) {
         QMessageBox::information(this, tr("error"), tr("error!"));
    }

    cv::resize(frame, frame, cv::Size(label->width(), label->height()));
    cv::cvtColor(frame,frame,CV_BGR2RGB);

    //detection ----- to add a method later
    cv::CascadeClassifier face_cascade("C:\\Users\\Administrator\\Desktop\\haarcascade_frontalface_alt.xml");
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
    int faceNumber = faces.size();
    for (int i = 0; i < faceNumber; i++)
    {
        cv::Rect face_i = faces[i];
        cv::rectangle(frame, face_i, cv::Scalar(255, 0, 255), 1, 8, 0);

//        cv::Mat face = gray(face_i);
//        cv::Mat face_resized;

//        // Get the height from the first image. We'll need this
//        // later in code to reshape the images to their original
//        // size AND we need to reshape incoming faces to this size:
//        //int im_width = images[0].cols;
//        //int im_height = images[0].rows;
//        cv::resize(face, face_resized, cv::Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
//        //Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
//        int prediction = model->predict(face_resized);

//        // Create the text we will annotate the box with:
//        string box_text = format("Prediction = %d", prediction);
//        // Calculate the position for annotated text (make sure we don't put illegal values in there):
//        int pos_x = std::max(face_i.tl().x - 10, 0);
//        int pos_y = std::max(face_i.tl().y - 10, 0);
//        // And now put it into the image:
//        putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);

    }

    QImage img= QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pix = QPixmap::fromImage(img);

    label->setPixmap(pix);
}
