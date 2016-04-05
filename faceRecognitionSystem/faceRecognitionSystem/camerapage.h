#ifndef CAMERAPAGE_H
#define CAMERAPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Ui 
{
	class CameraPage;
};

class CameraPage : public QWidget
{
	Q_OBJECT

public:
	CameraPage(QWidget *parent = 0);
	~CameraPage();

private:
	Ui::CameraPage *ui;

	QPushButton *open;
	QPushButton *close;
	QHBoxLayout *upLayout;
	QLabel *label;
	QVBoxLayout *layout;
};

#endif // CAMERAPAGE_H
