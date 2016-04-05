#ifndef PICTUREPAGE_H
#define PICTUREPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include "ui_picturepage.h"

namespace Ui {
	class PicturePage;
};

class PicturePage : public QWidget
{
	Q_OBJECT

public:
	PicturePage(QWidget *parent = 0);
	~PicturePage();

private:
	Ui::PicturePage *ui;

	QPushButton *open;
	QString imagePath;
	QLabel *label;
	QLabel *result;
	QHBoxLayout *upLayout;
	QVBoxLayout *layout;
	QImage *img;

private slots:
	void showImage();
};

#endif // PICTUREPAGE_H
