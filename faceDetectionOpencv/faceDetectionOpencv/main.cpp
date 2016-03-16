///////////////////////////////////////////////////////////////////////////////////////////////
//
//²Î¿¼£ºhttp://opencvexamples.blogspot.com/2013/10/face-detection-using-haar-cascade.html
//     http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html
//
///////////////////////////////////////////////////////////////////////////////////////////////

#include "opencv2/objdetect/objdetect.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;


int main(int argc, char** argv){
	Mat image;

	//Mat imread(const string& filename, int flags=1 )
	//@param flags    Flags specifying the color type of a loaded image
	//              CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_COLOR | CV_LOAD_IMAGE_GRAYSCALE | >0 | =0 | <0
	image = imread("images/godfather.jpg", CV_LOAD_IMAGE_COLOR);
	namedWindow("original", 1);
	imshow("original", image);

	//Constructor
	//Or:
	//	CascadeClassifier face_cascade;
	//	face_cascade.load("haarcascade_frontalface_alt.xml");
	CascadeClassifier face_cascade("haarcascade_frontalface_alt.xml");

	//Detects objects of different sizes in the input image and return as a list of rectangles.
	//void CascadeClassifier::detectMultiScale(const Mat& image, vector<Rect>& objects, double scaleFactor=1.1, int minNeighbors=3, int flags=0, Size minSize=Size(), Size maxSize=Size())
	//@param image   Matrix of the type CV_8U containing an image where objects are detected.
	//@param objects   Vector of rectangles where each rectangle contains the detected object.
	//@param scaleFactor   Parameter specifying how much the image size is reduced at each image scale.
	//@param miniNeighbors    Parameter specifying how many neighbors each candidate rectangle should have to retain it.
	//@param flags    Parameter with the same meaning for an old cascade as in the function cvHaarDetectObjects. It is not used for a new cascade.
	//@param minSize    Minimum possible object size. Objects smaller than that are ignored.
	//@param maxSize    Maximum possible object size. Objects larger than that are ignored.
	vector<Rect> faces;
	face_cascade.detectMultiScale(image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	/**
	for (int i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
		//draw ellipse:
		//void ellipse(Mat& img, Point center, Size axes, double angle, double startAngle, double endAngle, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
		//@param axes    Half of the size of the ellipse main axes.
		//@param angle    Ellipse rotation angle in degrees.
		//@param shift    Number of fractional bits in the coordinates of the center and values of axes.
		ellipse(image, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
	}
	**/

	//draw rectangle
	for (int i = 0; i < faces.size(); i++)
	{
		//void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, int lineType=8, int shift=0 )
		//void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
		//method 1:
		rectangle(image, faces[i], Scalar(255, 0, 255), 1, 8, 0);
		//method 2:
		/*Point pt1(faces[i].x, faces[i].y);
		Point pt2(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		rectangle(image, pt1, pt2, Scalar(255, 0, 255), 1, 8, 0);*/
	}

	imshow("Detected Face", image);

	waitKey(0);
	return 0;
}
