#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
  string infile = "sky.jpg";
  string outfile = "sky2.jpg";
  Mat img1, img2, img3, img4, img5;

  //create
    img1 = Mat(2,2, CV_8UC3, Scalar(0,0,255));
    //2x2 image, all pixels blue
    //CV_8UC3
      //each item (red, green or blue) 8 bits long
      //U: unsigned
      //C3: 3 channels

    img1 = Mat(2,2, CV_8UC3, Scalar::all(0));
    //all black
 
    img2 = Mat(img1); 
    //copy constructor
    //data is *not* copied

    img3 = img2;
    //data is *not* copied

    img4 = img1.clone();
    //data is copied

    img1.copyTo(img4);
    //data is copied
   
  //info
    cout << img1 << endl;
    cout << "data\n" << img1.data << endl;
    cout << "python\n" << format(img1,"python") << endl;
    //cout << "cvs\n" << format(img1,"cvs") << endl;
    cout << "numpy\n" << format(img1,"numpy") << endl;

    //cout << img1.size() << endl;
 
  //fileio
    img1 = imread( infile, 1 );
    imwrite( outfile, img1 );
 
  //highgui
    namedWindow( "sky", CV_WINDOW_AUTOSIZE );
    namedWindow( "gray", CV_WINDOW_AUTOSIZE );

    imshow( infile, img1 );
    imshow( "gray", img1 );

  //cvtColor( img1, gray_img1, CV_RGB2GRAY );


    waitKey(0);

 return 0;
}
