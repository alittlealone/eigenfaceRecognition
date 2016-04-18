////////////////////////////////////////////////////////////////////////////////
//api: http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html
////////////////////////////////////////////////////////////////////////////////

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace std;

int main(int, char**)
{
	vector<Mat> images;
	vector<int> labels;

	int im_width = images[0].cols;
	int im_height = images[0].rows;

	Ptr<FaceRecognizer> model = createFisherFaceRecognizer();
	model->train(images, labels);

	// open the default camera
	//VideoCapture cap(0);
	//open a video, just pass the video file name

	CascadeClassifier haar_cascade;
	haar_cascade.load("C:\\Users\\Administrator\\Desktop\\haarcascade_frontalface_alt.xml");
	
	VideoCapture *cap;
	//cap1 = new VideoCapture(0);
	cap = new VideoCapture("C:\\Users\\Administrator\\Desktop\\6185919-1.flv");

	//if (! cap.isOpened())  // check if we succeeded
	//	return -1;
	
	Mat frame;
	//namedWindow("edges", 1);
	for (;;)
	{
		*cap >> frame;
		// Clone the current frame:
		Mat original = frame.clone();
		// Convert the current frame to grayscale:
		Mat gray;
		cvtColor(original, gray, CV_BGR2GRAY);
		// Find the faces in the frame:
		vector< Rect_<int> > faces;
		haar_cascade.detectMultiScale(gray, faces);
		// At this point you have the position of the faces in
		// faces. Now we'll get the faces, make a prediction and
		// annotate it in the video. Cool or what?
		for (int i = 0; i < faces.size(); i++) {
			// Process face by face:
			Rect face_i = faces[i];
			// Crop the face from the image. So simple with OpenCV C++:
			Mat face = gray(face_i);
			// Resizing the face is necessary for Eigenfaces and Fisherfaces. You can easily
			// verify this, by reading through the face recognition tutorial coming with OpenCV.
			// Resizing IS NOT NEEDED for Local Binary Patterns Histograms, so preparing the
			// input data really depends on the algorithm used.
			//
			// I strongly encourage you to play around with the algorithms. See which work best
			// in your scenario, LBPH should always be a contender for robust face recognition.
			//
			// Since I am showing the Fisherfaces algorithm here, I also show how to resize the
			// face you have just found:
			Mat face_resized;
			cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);
			// Now perform the prediction, see how easy that is:
			int prediction = model->predict(face_resized);
			// And finally write all we've found out to the original image!
			// First of all draw a green rectangle around the detected face:
			rectangle(original, face_i, CV_RGB(0, 255, 0), 1);
			// Create the text we will annotate the box with:
			string box_text = format("Prediction = %d", prediction);
			// Calculate the position for annotated text (make sure we don't
			// put illegal values in there):
			int pos_x = std::max(face_i.tl().x - 10, 0);
			int pos_y = std::max(face_i.tl().y - 10, 0);
			// And now put it into the image:
			putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0, 255, 0), 2.0);
		}
		// Show the result:
		imshow("face_recognizer", original);
		// And display it:
		char key = (char)waitKey(20);
		// Exit this loop on escape:
		if (key == 27)
			break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}