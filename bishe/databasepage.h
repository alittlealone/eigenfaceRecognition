#ifndef DATABASEPAGE_H
#define DATABASEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QImage>
#include <QString>

#include "pca.h"

namespace Ui {
class DatabasePage;
}

class DatabasePage : public QWidget
{
    Q_OBJECT

public:
    explicit DatabasePage(QWidget *parent = 0);
    ~DatabasePage();

private:
    Ui::DatabasePage *ui;

    QLabel *label_choose;
    QComboBox *comboBox;
    QPushButton *setPath;
    QString databasePath;
    QPushButton *trainButton;
    QHBoxLayout *upLayout;

    QGroupBox *test;
    QString test_img_path;
    QPushButton *open;
    QLabel *test_img_label;
    QImage *test_img;
    QVBoxLayout *testLayout;

    QGroupBox *result;
    QPushButton *start;
    QLabel *result_string1;
    QString result_string1_str;
    QLabel *result_string2;
    QLabel *result_img_label;
    QImage *result_img;
    int predict_label;
    QVBoxLayout *resultLayout;

    QHBoxLayout *singleLayout;

    QGroupBox *total;
    QPushButton *total_predict;
    QLabel *total_string;
    QString total_string_str;
    QVBoxLayout *total_layout;
    QVBoxLayout *totalLayout;

    QVBoxLayout *layout;

    pca *pcaModel;

private slots:
    void setDatabasePath();
    void showTestImage();
    void train();
    void predict();
    void totalPredict();
};

#endif // DATABASEPAGE_H
