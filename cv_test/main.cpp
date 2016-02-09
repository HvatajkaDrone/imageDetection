#include <iostream>;
#include "opencv2\core\core.hpp";
#include "opencv2\highgui\highgui.hpp";
#include <stdlib.h>;
#include <stdio.h>;
#include "opencv2\imgproc\imgproc.hpp";

using namespace std;
using namespace cv;

int main()
{
	// Initialize captured frame from random camera (we have only one camera)
	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
	assert(capture);

	// Get width and height of capture image
	double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
		height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);

	// Captured frame
	IplImage* frame = 0;

	// Create window
	cvNamedWindow("Captured frame", CV_WINDOW_AUTOSIZE);

	while (true)
	{
		// Take frame from capture
		frame = cvQueryFrame(capture);

		// Show frame
		cvShowImage("Captured frame", frame);
	}

	cvReleaseCapture(&capture);
	cvDestroyWindow("Captured frame");

	return 0;
}