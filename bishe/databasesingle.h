#ifndef DATABASESINGLE_H
#define DATABASESINGLE_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QImage>
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace Ui {
class databaseSingle;
}

class databaseSingle : public QWidget
{
    Q_OBJECT

public:
    explicit databaseSingle(QWidget *parent = 0);
    ~databaseSingle();

private:
    Ui::databaseSingle *ui;

    QGroupBox *test;
    QGroupBox *result;
    QPushButton *open;
    QLabel *test_img;
    QImage *img;
    QVBoxLayout *testLayout;
    QVBoxLayout *resultLayout;
    QLabel *result_string1;
    QLabel *result_string2;
    QLabel *result_img;
    QHBoxLayout *layout;

private slots:
    void showTestImage();
};

#endif // DATABASESINGLE_H
