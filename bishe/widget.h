#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "ui_widget.h"
#include "databasepage.h"
#include "picturepage.h"
#include "camerapage.h"
#include "videopage.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    QLabel *sysName;
    QButtonGroup *buttonGroup;
    QPushButton *button_database;
    QPushButton *button_picture;
    QPushButton *button_camera;
    QPushButton *button_video;
    QLabel *info;
    QVBoxLayout *leftLayout;
    QStackedLayout *stackedLayout;

    DatabasePage *databasePage;
    PicturePage *picturePage;
    CameraPage *cameraPage;
    VideoPage *videoPage;

    QHBoxLayout *mainLayout;
};

#endif // MAINWIDGET_H
