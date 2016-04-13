#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    label = new QLabel;

    timer = new QTimer(this);

    capture = cvCaptureFromCAM(0); //cvCaptureFromCAM其实是一个宏，就是cvCreateCameraCapture的别名，0代表第一个摄像头。-1代表默认摄像头。

    if(capture==NULL){

        qDebug()<<"error!";

    }

    timer->start(50); //1000为1秒，50毫秒去取一帧

    connect(timer,SIGNAL(timeout()),this,SLOT(getFrame())); //超时就去取
}

Dialog::~Dialog()
{
    timer->stop(); //停止取帧

    cvReleaseCapture(&capture); //释放资源是个好习惯

    delete ui;
}


void Dialog::getFrame()

{

    frame = cvQueryFrame(capture); //从摄像头取帧

    QImage image = QImage((const uchar*)frame->imageData, frame->width, frame->height, QImage::Format_RGB888).rgbSwapped(); //简单地转换一下为Image对象，rgbSwapped是为了显示效果色彩好一些。

    ui->label->setPixmap(QPixmap::fromImage(image));


}


