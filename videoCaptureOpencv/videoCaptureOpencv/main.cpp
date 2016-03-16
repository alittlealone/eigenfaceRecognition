////////////////////////////////////////////////////////////////////////////////
//api: http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html
////////////////////////////////////////////////////////////////////////////////

#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
	// open the default camera
	//VideoCapture cap(0);
	//open a video, just pass the video file name
	VideoCapture cap("F:/Apple Steve Jobs The Crazy Ones - NEVER BEFORE AIRED 1997 - (Original Post).mp4");

	if (!cap.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		while (frame.empty())
			cap >> frame;
		cvtColor(frame, edges, CV_BGR2GRAY);
		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}