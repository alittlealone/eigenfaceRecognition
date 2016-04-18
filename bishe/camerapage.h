#ifndef CAMERAPAGE_H
#define CAMERAPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <opencv2/highgui/highgui.hpp> //to load video
#include <opencv2/imgproc/imgproc.hpp> //to manipulate
#include <opencv2/opencv.hpp>

namespace Ui {
class CameraPage;
}

class CameraPage : public QWidget
{
    Q_OBJECT

public:
    explicit CameraPage(QWidget *parent = 0);
    ~CameraPage();

private:
    Ui::CameraPage *ui;

    QPushButton *open;
    QPushButton *close;
    QHBoxLayout *upLayout;
    QLabel *label;
    QVBoxLayout *layout;

    QTimer *timer;
    CvCapture *capture;
//    cv::VideoCapture *capture;  // to capture video
    cv::Mat frame;

private slots:
    void playVideo();
    void displayFrame();
};

#endif // CAMERAPAGE_H
