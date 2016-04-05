#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>

#include "ui_mainwidget.h"

#include "databasepage.h"
#include "picturepage.h"
#include "camerapage.h"
#include "videopage.h"

namespace Ui 
{
	class mainWidget;
};

class mainWidget : public QWidget
{
	Q_OBJECT

public:
	mainWidget(QWidget *parent = 0);
	~mainWidget();

private:
	Ui::mainWidgetClass *ui;

	QLabel *sysName;
	QButtonGroup *buttonGroup;
	QPushButton *button_database;
	QPushButton *button_picture;
	QPushButton *button_camera;
	QPushButton *button_video;
	QLabel *info;
	QVBoxLayout *leftLayout;
	QStackedLayout *stackedLayout;

	DatabasePage *databasePage;
	PicturePage *picturePage;
	CameraPage *cameraPage;
	VideoPage *videoPage;

	QHBoxLayout *mainLayout;
};

#endif // MAINWIDGET_H
