#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

#include <iostream>

using namespace cv;
using namespace std;

/// Global variables

Mat reference = imread("van_gogh.jpg");


Mat src_gray;
Mat dst, detected_edges;

Mat src = reference.clone();

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";

void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }

void edgeDetection(){

  int k = 0;
  while (k != 1048603) {

    

    dst.create( src.size(), src.type() );

    /// Convert the image to grayscale
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Create a window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    /// Create a Trackbar for user to enter threshold
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

    /// Show the image
    CannyThreshold(0, 0);

    k = waitKey(1); //V2



  }

}

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */



/** @function main */
int main( int argc, char** argv )
{

   cout << "OpenCV version : " << CV_VERSION << endl;
  cout << "Major version : " << CV_MAJOR_VERSION << endl;
  cout << "Minor version : " << CV_MINOR_VERSION << endl;
  cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

  /// Load an image
  
/*
  if( !src.data )
  { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);
*/

  edgeDetection();


  return 0;
  }