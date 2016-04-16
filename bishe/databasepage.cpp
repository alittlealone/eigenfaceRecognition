#include "databasepage.h"
#include "ui_databasepage.h"

#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

#include <vector>
#include <string>

DatabasePage::DatabasePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabasePage)
{
    ui->setupUi(this);

    label_choose = new QLabel(tr("Please choose a database: "));
    comboBox = new QComboBox;
    comboBox->addItem(tr("AT&T"));
    comboBox->addItem(tr("Yale"));
    comboBox->addItem(tr("ORL"));
    setPath = new QPushButton(tr("setPath"));
    trainButton = new QPushButton(tr("train"));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(label_choose);
    upLayout->addWidget(comboBox);
    upLayout->addWidget(setPath);
    upLayout->addWidget(trainButton);

    connect(setPath, SIGNAL(clicked()), this, SLOT(setDatabasePath()));
    connect(setPath, SIGNAL(clicked()), this, SLOT(setLabel());
    connect(trainButton, SIGNAL(clicked()), this, SLOT(train()));

    test = new QGroupBox(tr("test"));
    open = new QPushButton(tr("Open"));
    test_img_label = new QLabel();

    testLayout = new QVBoxLayout;
    testLayout->addWidget(open);
    testLayout->addWidget(test_img_label);
    test->setLayout(testLayout);

    connect(open, SIGNAL(clicked()), this, SLOT(showTestImage()));

    result = new QGroupBox(tr("result"));
    start = new QPushButton(tr("Start"));
    result_string1 = new QLabel(tr("The picture is belong to : "));
    result_string2 = new QLabel(tr("This person's picture in database: "));
    result_img_label = new QLabel();

    resultLayout = new QVBoxLayout;
    resultLayout->addWidget(start);
    resultLayout->addWidget(result_string1);
    resultLayout->addWidget(result_string2);
    resultLayout->addWidget(result_img_label);
    result->setLayout(resultLayout);

    connect(start, SIGNAL(clicked()), this, SLOT(predict()));

    singleLayout = new QHBoxLayout;
    singleLayout->addWidget(test);
    singleLayout->addWidget(result);

    total = new QGroupBox(tr("total"));
    total_string = new QLabel(tr("The total precision is: "));
    total_layout = new QVBoxLayout;
    total_layout->addWidget(total_string);
    total->setLayout(total_layout);

    totalLayout = new QVBoxLayout;
    totalLayout->addWidget(total);


    layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addLayout(singleLayout);
    layout->addLayout(totalLayout);

    setLayout(layout);
}

DatabasePage::~DatabasePage()
{
    delete ui;
}

void DatabasePage::setDatabasePath()
{
    switch(this->comboBox->currentIndex())
    {
    case 0:
        databasePath = "F:/a/projects/pcaMat/pcaMat/images/ATT";
        break;
    case 1:
        databasePath = "F:/a/projects/pcaMat/pcaMat/images/YALE";
        break;
    case 2:
        databasePath = "F:/a/projects/pcaMat/pcaMat/images/ORL";
    }
}

void DatabasePage::setLabel()
{
    pcaModel->setLabel(databasePath.toStdString());
}

void DatabasePage::showTestImage()
{
    switch(this->comboBox->currentIndex())
    {
    case 0:
        test_img_path = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "F:/a/projects/pcaMat/pcaMat/images/ATTTest", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    case 1:
        test_img_path = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "F:/a/projects/pcaMat/pcaMat/images/YALETest", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    case 2:
        test_img_path = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "F:/a/projects/bishe/database/ORL/ORLTest", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    }
//    test_img_path = QFileDialog::getOpenFileName(this, tr("Open Image"),
//                                                 databasePath, tr("Image Files (*.png *.jpg *.bmp *.tif)"));
    if(test_img_path.isEmpty())
    {
        return;
    }
    else
    {
        test_img=new QImage;

        if(!(test_img->load(test_img_path)))
        {
            QMessageBox::information(this, tr("error"), tr("Failed to open this image!"));
            delete test_img;
            return;
        }
        this->test_img_label->setPixmap(QPixmap::fromImage(*test_img));
    }
}


void DatabasePage::train()
{
    pcaModel = new pca(databasePath.toStdString());
    pcaModel->train();
}

void DatabasePage::predict()
{
    Mat test = imread(test_img_path.toStdString(), 0);
    pcaModel->setTestData(test);
    pcaModel->predict();
    int predict = pcaModel->getPredictedLabel();
    result_img_label->setText(QString::number(predict));
}
