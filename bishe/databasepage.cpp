#include "databasepage.h"
#include "ui_databasepage.h"

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

    tabWidget = new QTabWidget;
    singleTab = new databaseSingle();
    totalTab = new databaseTotal();
    tabWidget->addTab(singleTab, tr("single analysis"));
    tabWidget->addTab(totalTab, tr("total analysis"));

    layout = new QVBoxLayout;
    layout->addLayout(upLayout);
    layout->addWidget(tabWidget);

    setLayout(layout);
}

DatabasePage::~DatabasePage()
{
    delete ui;
}
