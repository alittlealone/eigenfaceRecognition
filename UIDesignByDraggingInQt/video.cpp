#include "video.h"
#include "ui_video.h"

video::video(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::video)
{
    ui->setupUi(this);
}

video::~video()
{
    delete ui;
}
