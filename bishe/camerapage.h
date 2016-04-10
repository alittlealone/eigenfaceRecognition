#ifndef CAMERAPAGE_H
#define CAMERAPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <opencv2/highgui/highgui.hpp> //to load video
#include <opencv2/imgproc/imgproc.hpp> //to manipulate

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

    QTimer *timer; // the timer that will refresh the widget
    cv::VideoCapture *capture;  // to capture video
    cv::Mat frame; // the frame that we will copy readed images from video

private slots:
    void playVideo();
    void displayFrame(); // the method that will display video
};

#endif // CAMERAPAGE_H
