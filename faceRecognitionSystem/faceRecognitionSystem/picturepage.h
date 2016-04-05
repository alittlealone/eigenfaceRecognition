#ifndef PICTUREPAGE_H
#define PICTUREPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
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
	QLabel *label;
	QLabel *result;
	QHBoxLayout *upLayout;
	QVBoxLayout *layout;
};

#endif // PICTUREPAGE_H
