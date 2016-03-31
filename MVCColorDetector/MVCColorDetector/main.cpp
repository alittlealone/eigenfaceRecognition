///////////////////////////////////////////////////////////////////////////////////////////////////////
// The code is from book:
//    "OpenCV 2 Computer Vision Application Programming Cookbook" (Chapter 3)
// With some modifications made by myself to make it run in VS.
// I use this code to learn how to use Qt and opencv in VS, and also learn to use MVC architecture.
///////////////////////////////////////////////////////////////////////////////////////////////////////


#include "mvccolordetector.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MVCColorDetector w;
	w.show();
	return a.exec();
}
