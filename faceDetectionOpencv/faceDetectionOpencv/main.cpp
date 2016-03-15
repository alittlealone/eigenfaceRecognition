///////////////////////////////////////////////////////////////////////////////////////////////
//
//²Î¿¼£ºhttp://opencvexamples.blogspot.com/2013/10/face-detection-using-haar-cascade.html
//
///////////////////////////////////////////////////////////////////////////////////////////////

#include "opencv2/objdetect/objdetect.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


CascadeClassifier face_cascade;
void detectAndDisplay(Mat frame);

int main(int argc, char** argv){
	Mat image;
	image = imread("images/godfather.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("original", 1);
	imshow("original", image);

	CascadeClassifier face_cascade("haarcascade_frontalface_alt.xml");

	vector<Rect> faces;
	face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}

	imshow("Detected Face", image);

	waitKey(0);
	return 0;
}
