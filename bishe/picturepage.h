#ifndef PICTUREPAGE_H
#define PICTUREPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QString>

#include <vector>

#include "pca.h"

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

    pca *pcaPictureModel;
    std::vector<int> labelVector;

    QPushButton *setTrainPath;
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
    void setDatabasePath();
    void showImage();
    void recognize();
    void labels();

};

#endif // PICTUREPAGE_H
