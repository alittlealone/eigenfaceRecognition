#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <cv.h>

#include <highgui.h>

#include <QTimer>

#include <QPixmap>

#include <QLabel>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    CvCapture *capture; //highgui 里提供的一个专门处理摄像头图像的结构体

    IplImage *frame; //摄像头每次抓取的图像为一帧，使用该指针指向一帧图像的内存空间


    QTimer *timer; //定时器用于定时取帧，上面说的隔一段时间就去取就是用这个实现。

    QLabel *label;


private slots:

    void getFrame(); //实现定时从摄像头取图并显示在label上的功能。
};

#endif // DIALOG_H

