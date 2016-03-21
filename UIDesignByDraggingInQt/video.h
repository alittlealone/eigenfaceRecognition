#ifndef VIDEO_H
#define VIDEO_H

#include <QMainWindow>

namespace Ui {
class video;
}

class video : public QMainWindow
{
    Q_OBJECT

public:
    explicit video(QWidget *parent = 0);
    ~video();

private:
    Ui::video *ui;
};

#endif // VIDEO_H
