#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src,  rotate_dst, M;
Mat reference = imread("van_gogh.jpg");
int phi= 180;
int xsize = 10;
int const max_phi = 360;
int const max_xsize = 100;

void RotateAngle( int, void* );
void RotateAngle main( int argc, char** argv )
{
  CommandLineParser parser( argc, argv, "{@input | ../data/LinuxLogo.jpg | input image}" );
  src = reference;
  if( src.empty() )
  {
    cout << "Could not open or find the image!\n" << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }
  namedWindow( "Ajust rotation angle", WINDOW_AUTOSIZE );
  moveWindow( "Ajust rotation angle", src.cols, 0 );
  createTrackbar( "Ajust angle :\n ", "Ajust rotation angle",
          &phi, max_phi,
          RotateAngle );
  createTrackbar( "Ajust crop factor :\n ", "Ajust rotation angle",
          &xsize, max_xsize,
          RotateAngle );

  RotateAngle( 0, 0 );
  waitKey(0);

}
void RotateAngle( int, void* )
{
   Point2f center(src.cols/2, src.rows/2);
   double rotationAngle=phi-180;
   double scale=(float)xsize/10;

   Point2f pc(src.cols/2., src.rows/2.);
   M = getRotationMatrix2D(pc, rotationAngle, scale);

   warpAffine(src, rotate_dst, M, src.size());

   imshow( "Ajust rotation angle", rotate_dst );


}
