#ifndef VIDEOPAGE_H
#define VIDEOPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QTimer>

#include <opencv2/highgui/highgui.hpp> //to load video
#include <opencv2/imgproc/imgproc.hpp> //to manipulate images

namespace Ui {
class VideoPage;
}

class VideoPage : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPage(QWidget *parent = 0);
    ~VideoPage();

private:
    Ui::VideoPage *ui;

    QPushButton *open;
    QString videoPath;
    QHBoxLayout *upLayout;
    QVBoxLayout *layout;
    QLabel *label;

    QTimer *timer; // the timer that will refresh the widget
    cv::VideoCapture *capture;  // to capture video
    cv::Mat frame; // the frame that we will copy readed images from video

private slots:
    void playVideo();
    void displayFrame(); // the method that will display video
};

#endif // VIDEOPAGE_H
