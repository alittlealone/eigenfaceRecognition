#include "camera.h"
#include "ui_camera.h"

camera::camera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::camera)
{
    ui->setupUi(this);
}

camera::~camera()
{
    delete ui;
}
