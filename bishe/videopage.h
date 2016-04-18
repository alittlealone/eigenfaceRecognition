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

#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "pca.h"

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

    pca *pcaVideoModel;
    std::vector<int> labelVector;
    int im_width;
    int im_height;

    bool isPause;

    QPushButton *setDatabase;
    QPushButton *train;
    QPushButton *open;
    QPushButton *pause;
//    QPushButton *close;
    QString videoPath;
    QHBoxLayout *upLayout;
    QVBoxLayout *layout;
    QLabel *label;

    QTimer *timer; // the timer that will refresh the widget
    cv::VideoCapture *capture;  // to capture video
    cv::Mat frame; // the frame that we will copy readed images from video

private slots:
    void setDatabasePath();
    void labels();
    void trainModel();
    void playVideo();
    void displayFrame();
    void pauseVideo();
//    void closeVideo();
};

#endif // VIDEOPAGE_H
