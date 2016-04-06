#ifndef VIDEOPAGE_H
#define VIDEOPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFileDialog>

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

private slots:
    void setVideoPath();
};

#endif // VIDEOPAGE_H
