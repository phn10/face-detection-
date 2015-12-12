#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\objdetect\objdetect.hpp>

#include <iostream>
#include <stdio.h>

 using namespace std;
 using namespace cv;

 
void detectAndDisplay( Mat frame );

 /** Global variables */
 String face_cascade_name = "D:\\opencv2.4.9\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
 String eyes_cascade_name = "D:\\opencv2.4.9\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";
 CascadeClassifier face_cascade;
 CascadeClassifier eyes_cascade;
 string window_name = "Capture - Face detection";
 RNG rng(12345);

 /** @function main */
 int main( int argc, const char** argv )
 {
   CvCapture* capture;
   Mat frame;

   //-- 1. Load the cascades
   if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); waitKey(0); return -1; };
   if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading\n"); waitKey(0); return -1; };

   VideoCapture cap(0);
   if (!cap.isOpened())
   {
	   cout << "Cannot read file. " << endl;
	   waitKey(0);
	   return -1;
   }

   while( true )
   {
	   cap.retrieve(frame);
		bool bSuccess = cap.read(frame);
		if(!bSuccess)
		{
			cout << "Cannot read frames." << endl;
			waitKey(0);
			break;
		}

		detectAndDisplay(frame);
		
		if(waitKey(10) == 27)
		{
			cout << "Exit" << endl;
			break;
		}
    }
   return 0;
 }

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(40, 40) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( frame, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 0, 0, 255 ), 1, 8, 0 );

    Mat faceROI = frame_gray( faces[i] );
    std::vector<Rect> eyes;
  }
  
  
  
  imshow( window_name, frame );
 }
