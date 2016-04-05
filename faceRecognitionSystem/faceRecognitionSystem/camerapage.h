#ifndef CAMERAPAGE_H
#define CAMERAPAGE_H

#include <QWidget>

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
};

#endif // CAMERAPAGE_H
