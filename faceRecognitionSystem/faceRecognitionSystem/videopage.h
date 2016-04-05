#ifndef VIDEOPAGE_H
#define VIDEOPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
namespace Ui {class VideoPage;};

class VideoPage : public QWidget
{
	Q_OBJECT

public:
	VideoPage(QWidget *parent = 0);
	~VideoPage();

private:
	Ui::VideoPage *ui;

	QPushButton *open;
	QHBoxLayout *upLayout;
	QVBoxLayout *layout;
	QLabel *label;
};

#endif // VIDEOPAGE_H
