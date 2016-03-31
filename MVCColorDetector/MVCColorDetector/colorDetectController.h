#ifndef CD_CNTRLLR
#define CD_CNTRLLR

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "colorDetector.h"

class ColorDetectController {
	
private:

	static ColorDetectController *singleton;

	ColorDetector *cdetect;

	// The image to be processed
	cv::Mat image;
	cv::Mat result;

public:

	ColorDetectController() {
		cdetect = new ColorDetector();
	}

	void setColorDistanceThreshold(int distance) {
		cdetect->setColorDistanceThreshold(distance);
	}

	int getColorDistaanceThreshold() const {
		return cdetect->getColorDistanceThreshold();
	}

	void setTargetColor(unsigned char red, unsigned char green, unsigned char blue) {
		cdetect->setTargetColor(red, green, blue);
	}

	void getTargetColor(unsigned char &red, unsigned char &green, unsigned char &blue) const {
		cv::Vec3b color = cdetect->getTargetColor();

		red = color[2];
		green = color[1];
		blue = color[0];
	}

	bool setInputImage(std::string filename) {
		image = cv::imread(filename);
		if (!image.data)
			return false;
		else
			return true;
	}

	const cv::Mat getInputImage() const {
		return image;
	}

	void process() {
		result = cdetect->process(image);
	}

	const cv::Mat getLastResult() const {
		return result;
	}

	~ColorDetectController() {
		delete cdetect;
	}

	//Singleton static members
	static ColorDetectController *getInstance() {
		if (singleton == 0)
			singleton = new ColorDetectController;
		return singleton;
	}

	static void destroy() {
		if (singleton != 0) {
			delete singleton;
			singleton = 0;
		}
	}

};

#endif