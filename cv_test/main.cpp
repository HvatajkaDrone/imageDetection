//#include "opencv2\opencv.hpp";
//#include "opencv2\highgui\highgui.hpp";
//
//using namespace cv;
//
//int main()
//{
//	// Initialize captured frame from random camera (we have only one camera)
//	CvCapture* capture = cvCreateCameraCapture(CV_CAP_ANY);
//
//	// Get width and height of capture image
//	double width = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),
//		height = cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
//
//	// Captured frame
//	IplImage* frame = 0;
//
//	// Create window
//	cvNamedWindow("Captured frame", CV_WINDOW_AUTOSIZE);
//
//	while (true)
//	{
//		// Take frame from capture
//		frame = cvQueryFrame(capture);
//
//		if (frame == NULL)
//		{
//			break;
//		}
//
//		// Show frame
//		cvShowImage("Captured frame", frame);
//	}
//
//	cvReleaseCapture(&capture);
//	cvDestroyWindow("Captured frame");
//	
//	return 0;
//}

//
// демонстрация cvMinEnclosingCircle()
//
//
// http://robocraft.ru
//

#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

CvSeq* getContours(char* filename, CvMemStorage* storage)
{
	IplImage* image = cvLoadImage(filename, 1);

	image = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

	cvConvertImage(image, image, CV_BayerRG2GRAY);
	cvInRangeS(image, cvScalar(40), cvScalar(150), image);

	CvSeq* contours = 0;

	cvFindContours(image, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));

	return contours;
}

int main()
{
	char* cont_name = "contour.jpg";
	IplImage* cont_image = cvLoadImage(cont_name);

	char* det_name = "shapes.jpg";
	IplImage* det_image = cvLoadImage(det_name);

	CvMemStorage* det_storage = cvCreateMemStorage(0);
	CvSeq* det_contours = getContours("megan.jpg", det_storage);
	
	CvMemStorage* base_storage = cvCreateMemStorage(0);
	CvSeq* cont_image = getContours("megan.jpg", base_storage);

	CvSeq* seqM = 0;
	double matchM = 1000;

	// поиск лучшего совпадения контуров по их моментам 
	for (CvSeq* seq0 = det_contours; seq0 != 0; seq0 = seq0->h_next){
		double match0 = cvMatchShapes(seq0, cont_image, CV_CONTOURS_MATCH_I3);
		if (match0 < matchM){
			matchM = match0;
			seqM = seq0;
		}
	}

	cvDrawContours(, seqM, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8);

	return 0;
}