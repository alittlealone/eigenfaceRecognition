#include "picturepage.h"
#include "ui_picturepage.h"
#include <QPixmap>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>

PicturePage::PicturePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicturePage)
{
    ui->setupUi(this);

    open = new QPushButton(tr("Open"));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(open);
    upLayout->addStretch();

    label = new QLabel;
    result = new QLabel(tr("Total number of person in the picture is: "));

    connect(open, SIGNAL(clicked()), this, SLOT(showImage()));

    layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addWidget(label);
    layout->addWidget(result);

    setLayout(layout);
}

PicturePage::~PicturePage()
{
    delete ui;
}

void PicturePage::showImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                            "E://图片", tr("Image Files (*.png *.jpg *.bmp *.tif)"));

    if(imagePath.isEmpty())
    {
        return;
    }
    else
    {
        img=new QImage;

        if(!(img->load(imagePath)))
        {
            QMessageBox::information(this,
                                     tr("打开图像失败"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
        this->label->setPixmap(QPixmap::fromImage(*img));
    }
}
