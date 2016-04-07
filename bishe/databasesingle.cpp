#include "databasesingle.h"
#include "ui_databasesingle.h"

#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

//#include "databasepage.h"

databaseSingle::databaseSingle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::databaseSingle)
{    
    ui->setupUi(this);

    test = new QGroupBox(tr("test"));
    open = new QPushButton(tr("Open"));
    test_img = new QLabel();

    testLayout = new QVBoxLayout;
    testLayout->addWidget(open);
    testLayout->addWidget(test_img);
    test->setLayout(testLayout);

    connect(open, SIGNAL(clicked()), this, SLOT(showTestImage()));

    result = new QGroupBox(tr("result"));
    result_string1 = new QLabel(tr("The picture is belong to : "));
    result_string2 = new QLabel(tr("This person's picture in database: "));
    result_img = new QLabel();

    resultLayout = new QVBoxLayout;
    resultLayout->addWidget(result_string1);
    resultLayout->addWidget(result_string2);
    resultLayout->addWidget(result_img);
    result->setLayout(resultLayout);

    layout = new QHBoxLayout;
    layout->addWidget(test);
    layout->addWidget(result);

    setLayout(layout);
}

databaseSingle::~databaseSingle()
{
    delete ui;
}

void databaseSingle::showTestImage()
{
    QString imagePath;

    switch(qobject_cast<databasePage*>(parentWidget())->comboBox()->currentIndex())
    {
    case 0:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                "database//ATT//", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    case 1:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                "database//YALE//", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    case 2:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                "database//ORL//", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    case 3:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                "database//FERET", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    }

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
        this->test_img->setPixmap(QPixmap::fromImage(*img));
    }
}
