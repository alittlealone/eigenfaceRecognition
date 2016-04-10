#include "databasepage.h"
#include "ui_databasepage.h"

#include <QString>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

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
    comboBox->addItem(tr("FERET"));

    upLayout = new QHBoxLayout;
    upLayout->addWidget(label_choose);
    upLayout->addWidget(comboBox);

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
    resultLayout->addWidget(result_string1);
    resultLayout->addWidget(result_string2);
    resultLayout->addWidget(result_img_label);
    result->setLayout(resultLayout);

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

void DatabasePage::showTestImage()
{
    QString imagePath;

    switch(this->comboBox->currentIndex())
    {
    case 0:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "F:/a/projects/bishe/database/ATT/test", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    case 1:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "F:/a/projects/bishe/database/YALE/test", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    case 2:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "database//ORL//", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    case 3:
        imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                 "database//FERET", tr("Image Files (*.png *.jpg *.bmp *.tif)"));
        break;
    }

    if(imagePath.isEmpty())
    {
        return;
    }
    else
    {
        test_img=new QImage;

        if(!(test_img->load(imagePath)))
        {
            QMessageBox::information(this, tr("error"), tr("Failed to open this image!"));
            delete test_img;
            return;
        }
        this->test_img_label->setPixmap(QPixmap::fromImage(*test_img));
    }
}
