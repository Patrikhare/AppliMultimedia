#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src,  brightness_dst;
Mat reference = imread("van_gogh.jpg");
int beta= 50;
int alpha = 50;
int const max_beta = 100;
int const max_alpha = 100;

void BrightnessContrast( int, void* );
void BrightnessContrast_main( int argc, char** argv )
{
  CommandLineParser parser( argc, argv, "{@input | ../data/LinuxLogo.jpg | input image}" );
  src = reference;
  if( src.empty() )
  {
    cout << "Could not open or find the image!\n" << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }
  namedWindow( "Ajust Brightness and Contrast", WINDOW_AUTOSIZE );
  moveWindow( "Ajust Brightness and Contrast", src.cols, 0 );
  createTrackbar( "Brightness :\n ", "Ajust Brightness and Contrast",
          &beta, max_beta,
          BrightnessContrast );
  createTrackbar( "contrast :\n ", "Ajust Brightness and Contrast",
          &alpha, max_alpha,
          BrightnessContrast );

  BrightnessContrast( 0, 0 );
  waitKey(0);
  return 0;
}
void BrightnessContrast( int, void* )
{
  float alpha2= (float) alpha/50;
  float beta2=beta-50;
  Mat element= Mat::zeros( src.size(), src.type() );
  for( int y = 0; y < src.rows; y++ ) {
        for( int x = 0; x < src.cols; x++ ) {
            for( int c = 0; c < src.channels(); c++ ) {
                element.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha2*src.at<Vec3b>(y,x)[c] + beta2 );
            }
        }
    }
   brightness_dst = element;
   imshow( "Ajust Brightness and Contrast", brightness_dst );


}