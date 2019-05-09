#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src, ErosionDilation_dst;
Mat reference = imread("van_gogh.jpg");
int erosiondilation= 0;
int erosiondilation_size = 0;
int erosiondilation_elem = 0;

int const max_elem = 2;
int const max_size = 21;
void ErosionDilation( int, void* );
int ErosionDilation_main( int argc, char** argv )
{
  CommandLineParser parser( argc, argv, "{@input | ../data/LinuxLogo.jpg | input image}" );
  src = reference;
  if( src.empty() )
  {
    cout << "Could not open or find the image!\n" << endl;
    cout << "Usage: " << argv[0] << " <Input image>" << endl;
    return -1;
  }
  namedWindow( "Erosion/Dilation", WINDOW_AUTOSIZE );
  moveWindow( "Erosion/Dilation", src.cols, 0 );
  createTrackbar( "erosion or dilation:\n 0: dilation \n 1: erosion ", "Erosion/Dilation",
          &erosiondilation, 1,
          ErosionDilation );
  createTrackbar( "shape type:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion/Dilation",
          &erosiondilation_elem, max_elem,
          ErosionDilation);
  createTrackbar( "size:\n 2n +1", "Erosion/Dilation",
          &erosiondilation_size, max_size,
          ErosionDilation );
  ErosionDilation( 0, 0 );
  waitKey(0);
  return 0;
}
void ErosionDilation( int, void* )
{
  int erosiondilation_type = 0;
  if( erosiondilation_elem == 0 ){ erosiondilation_type = MORPH_ELLIPSE; }
  else if( erosiondilation_elem == 1 ){ erosiondilation_type = MORPH_RECT; }
  else if( erosiondilation_elem == 2) { erosiondilation_type = MORPH_CROSS; }

  if( erosiondilation == 0 ){ 
                       Mat element = getStructuringElement( erosiondilation_type,
                       Size( 2*erosiondilation_size + 1, 2*erosiondilation_size+1 ),
                       Point( erosiondilation_size, erosiondilation_size ) );
                       erode( src, ErosionDilation_dst, element );
  }
  else if( erosiondilation == 1 ){
                       Mat element2 = getStructuringElement( erosiondilation_type,
                       Size( 2*erosiondilation_size + 1, 2*erosiondilation_size+1 ),
                       Point( erosiondilation_size, erosiondilation_size ) );
                       dilate( src, ErosionDilation_dst, element2 );
  
  }
  imshow( "Erosion/Dilation", ErosionDilation_dst );
}