#ifndef MVCCOLORDETECTOR_H
#define MVCCOLORDETECTOR_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QColorDialog>

#include "cv.h"
#include "highgui.h"

#include "colorDetectController.h"
#include "colordetector.h"

#include "ui_mvccolordetector.h"

class MVCColorDetector : public QMainWindow
{
	Q_OBJECT

public:
	MVCColorDetector(QWidget *parent = 0);
	~MVCColorDetector();

protected:
	void changeEvent(QEvent *e);
	void displayMat(const cv::Mat &img);

private:
	Ui::MVCColorDetectorClass *ui;

private slots:
	//void on_pushButton_color_clicked();
	void processColorDetection();
	void on_verticalSlider_Threshold_valueChanged(int value);

	void setColor();
	void setImage();
};

#endif // MVCCOLORDETECTOR_H
