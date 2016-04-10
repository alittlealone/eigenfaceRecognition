#ifndef PICTUREPAGE_H
#define PICTUREPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QString>

namespace Ui {
class PicturePage;
}

class PicturePage : public QWidget
{
    Q_OBJECT

public:
    explicit PicturePage(QWidget *parent = 0);
    ~PicturePage();

private:
    Ui::PicturePage *ui;

    QPushButton *open;
    QPushButton *start;
    QLabel *label;
    QLabel *result;
    QHBoxLayout *upLayout;
    QVBoxLayout *layout;
    QString imagePath;
    QImage *img;

    QString number_label;
    int faceNumber;

private slots:
    void showImage();
    void recognize();
};

#endif // PICTUREPAGE_H
