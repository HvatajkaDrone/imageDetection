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

//void getContours(const char* filename, CvMemStorage* storage, CvSeq* contours)
//{
//	IplImage* image = cvLoadImage(filename);
//
//	cvNamedWindow("Binary", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Binary", image);
//
//	cvWaitKey(0);
//	
//	IplImage* bin = cvCreateImage(cvGetSize(image), 8, 1);
//
//	cvCanny(image, bin, 50, 200);
//
//	cvNamedWindow("Canny", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Canny", bin);
//
//	cvWaitKey(0);
//
//	int contoursCont = cvFindContours(bin, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));
//}

int main()
{
	char* cont_name = "rect.jpg";
	IplImage* image_contour = cvLoadImage(cont_name);

	char* det_name = "figures.jpg";
	IplImage* det_image = cvLoadImage(det_name);

	CvMemStorage* det_storage = cvCreateMemStorage(0);
	CvSeq* det_contours = 0;
	//getContours(det_name, det_storage, det_contours);
	

	IplImage* imageI = cvLoadImage(det_name);
	IplImage* binI = cvCreateImage(cvGetSize(imageI), 8, 1);

	cvCanny(imageI, binI, 50, 200);

	cvFindContours(binI, det_storage, &det_contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));


	CvMemStorage* base_storage = cvCreateMemStorage(0);
	CvSeq* cont_image = 0; 
	//getContours(cont_name, base_storage, cont_image);


	IplImage* imageT = cvLoadImage(cont_name);
	IplImage* binT = cvCreateImage(cvGetSize(imageT), 8, 1);

	cvCanny(imageT, binT, 50, 200);

	cvFindContours(binT, base_storage, &cont_image, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0));


	CvSeq* seqI = 0,
		*seqT = 0;
	double matchM = 1000;

	// поиск лучшего совпадения контуров по их моментам 
	for (CvSeq* seq0 = det_contours; seq0 != 0; seq0 = seq0->h_next)
	{
		for (CvSeq* seq1 = cont_image; seq1 != 0; seq1 = seq1->h_next)
		{
			double match0 = cvMatchShapes(seq0, seq1, CV_CONTOURS_MATCH_I3); //cvMatchShapes(seq0, cont_image, CV_CONTOURS_MATCH_I3);
			if (match0 < matchM)
			{
				matchM = match0;

				seqT = seq1;
				seqI = seq0;
			}
		}
	}
	cvDrawContours(image_contour, seqT, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8);
	cvDrawContours(det_image, seqI, CV_RGB(52, 201, 36), CV_RGB(36, 201, 197), 0, 2, 8);

	cvNamedWindow("Detection image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Detection image", det_image);

	cvNamedWindow("Contour image", CV_WINDOW_AUTOSIZE);
	cvShowImage("Contour image", image_contour);

	cvWaitKey();

	return 0;
}