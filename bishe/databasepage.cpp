#include "databasepage.h"
#include "ui_databasepage.h"

#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

#include <vector>
#include <string>
#include <io.h>

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
    result_string1_str = "The picture is belong to : ";
    result_string1 = new QLabel(result_string1_str);
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
    total_predict = new QPushButton(tr("predict"));
    total_string_str = "The total precision is: ";
    total_string = new QLabel(total_string_str);
    total_layout = new QVBoxLayout;
    total_layout->addWidget(total_predict);
    total_layout->addWidget(total_string);
    total->setLayout(total_layout);

    connect(total_predict, SIGNAL(clicked()), this, SLOT(totalPredict()));

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
                                                 "F:/a/projects/pcaMat/pcaMat/images/ORLTest", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
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

    result_string1_str = "The picture is belong to : ";
    result_string1->setText(result_string1_str);
}


void DatabasePage::train()
{
    pcaModel = new pca(databasePath.toStdString());
    pcaModel->setLabel(databasePath.toStdString());
    pcaModel->train();
    QMessageBox::information(this, tr("finish"), tr("Training finish!"));
}

void DatabasePage::predict()
{
    Mat test = imread(test_img_path.toStdString(), 0);
    pcaModel->setTestData(test);
    pcaModel->predict();
    int predict = pcaModel->getPredictedLabel();


    result_string1_str.append(QString::number(predict));
    result_string1->setText(result_string1_str);

    result_img=new QImage;
    QString result_image_path;
    switch(this->comboBox->currentIndex())
    {
    case 0:
        if(predict == 1)
            result_image_path = "F:/a/projects/pcaMat/pcaMat/images/ATT/01.BMP";
        else
            result_image_path = "F:/a/projects/pcaMat/pcaMat/images/ATT/" + QString::number(9 * (predict - 1) + 1) + ".BMP";
        break;
    case 1:
        result_image_path = "F:/a/projects/pcaMat/pcaMat/images/YALE/s" + QString::number(11 * (predict - 1) + 1) + ".bmp";
        break;
    case 2:
        if(predict < 10)
            result_image_path = "F:/a/projects/pcaMat/pcaMat/images/ORL/orl_00" + QString::number(predict) + "_001.bmp";
        else
            result_image_path = "F:/a/projects/pcaMat/pcaMat/images/ORL/orl_0" + QString::number(predict) + "_001.bmp";
    }
    if(!(result_img->load(result_image_path)))
    {
        QMessageBox::information(this, tr("error"), tr("Failed to open this image!"));
        delete test_img;
        return;
    }
    this->result_img_label->setPixmap(QPixmap::fromImage(*result_img));
}

void getFilesTest(string path, string exd, vector<string>& files) {
    //文件句柄
    long   hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string pathName, exdName;

    //两个字符串相等，strcmp函数返回0
    if (0 != strcmp(exd.c_str(), ""))
    {
        exdName = "\\*." + exd;
    }
    else
    {
        exdName = "\\*";
    }

    //_findfirst如果失败，则返回-1
    if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是文件夹中仍有文件夹,迭代之
            //如果不是,加入列表
            if ((fileinfo.attrib &  _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFilesTest(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
            }
            else
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }

//    else
//        QMessageBox::information(this, tr("error"), tr("Failed to get file!"));
}

void DatabasePage::totalPredict()
{
    total_string_str = "The total precision is: ";
    total_string->setText(total_string_str);

    QString testFolderPath;
    switch(this->comboBox->currentIndex())
    {
    case 0:
        testFolderPath = "F:/a/projects/pcaMat/pcaMat/images/ATTTest";
        break;
    case 1:
        testFolderPath = "F:/a/projects/pcaMat/pcaMat/images/YALETest";
        break;
    case 2:
        testFolderPath = "F:/a/projects/pcaMat/pcaMat/images/ORLTest";
        break;
    }

    vector<string> testFiles;
    getFilesTest(testFolderPath.toStdString(), "bmp", testFiles);

    int totalNumber = testFiles.size();
    int accurateNumber = 0;
    for (int i = 0; i < totalNumber; i++) {
        Mat test = imread(testFiles[i], 0);
        pcaModel->setTestData(test);
        pcaModel->predict();
        int predict = pcaModel->getPredictedLabel();
        if(i + 1 == predict)
            accurateNumber++;
    }

    QMessageBox::information(this, tr("finish"), tr("Finish calculating accuracy!"));

    double accuracy = (double)accurateNumber / totalNumber;

    total_string_str.append(QString::number(accuracy * 100)).append("%");
    total_string->setText(total_string_str);
}
