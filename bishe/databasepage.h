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
    QHBoxLayout *upLayout;

    QGroupBox *test;
    QPushButton *open;
    QLabel *test_img_label;
    QImage *test_img;
    QVBoxLayout *testLayout;

    QGroupBox *result;
    QPushButton *start;
    QLabel *result_string1;
    QLabel *result_string2;
    QLabel *result_img_label;
    QImage *result_img;
    QVBoxLayout *resultLayout;

    QHBoxLayout *singleLayout;

    QGroupBox *total;
    QLabel *total_string;
    QVBoxLayout *total_layout;
    QVBoxLayout *totalLayout;

    QVBoxLayout *layout;

private slots:
    void showTestImage();

};

#endif // DATABASEPAGE_H
