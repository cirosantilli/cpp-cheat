#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
  string infile = "input/sky.jpg";
  string outfile = "sky2.jpg";
  double d;
  int i2, nRows, nCols, channels;
  Mat I, I1, I2, I3, I4, I5;

  //create
    I = Mat(2,2, CV_8UC3, Scalar(0,127,255));
    //2x2 image, r=0, g=127 b=255
    //CV_8UC3
      //each item (red, green or blue) 8 bits long
      //U: unsigned
      //C3: 3 channels

    I1 = Mat(2,2, CV_8UC3, Scalar::all(0));
    //all black

    I2 = Mat(I);
    //copy constructor
    //data is *not* copied

    I3 = I2;
    //data is *not* copied

    I4 = I1.clone();
    //data is copied

    I1.copyTo(I4);
    //data is copied

  cout << "info" << endl;
    I = Mat(2,2, CV_8UC3, Scalar(0,127,255));
    cout << "cout" << endl << I << endl;
    cout << "python" << endl << format(I,"python") << endl;
    //cout << "cvs" << endl << format(I,"cvs") << endl;
    cout << "numpy" << endl << format(I,"numpy") << endl;

    cout << "rows" << endl << I.rows << endl;
    //2
    cout << "cols" << endl << I.cols << endl;
    //2
    cout << "step" << endl << I.step << endl;
    cout << "depth()" << endl << I.depth() << endl;
    //CV_8U
    cout << "CV_8U" << endl << CV_8U << endl;
    //CV_8U
    cout << "channels()" << endl << I.channels() << endl;
    //3
    cout << "isContinuous()" << endl << I.isContinuous() << endl;
    //?
    //if true, storage is one big array in memery
      //and can therefore be looped with pointers directly
    //otherwise, stored rows are continuous in memory

  cout << "access elements" << endl;

    cout << "row pointers" << endl;
      CV_Assert(I.depth() == CV_8U);
      channels = I.channels();
      nRows = I.rows;
      nCols = I.cols * channels;
      if (I.isContinuous())
      {
          nCols *= nRows;
          nRows = 1;
      }
      uchar* p;
      for(int i = 0; i < nRows; ++i)
      {
          p = I.ptr<uchar>(i);
          for (int j = 0; j < nCols; ++j)
          {
              cout << (int)p[j] << " ";
              //p[j] = 0; //assigment is ok too
          }
          cout << endl;
          for (int j = 0; j < nCols; j=j+channels)
          {
              //THERE IS SOMETHING ABOUT COLORS BEING INVERTED as b,g,r and not r,g,b
              cout << "b " << (int)p[j] << endl;
              cout << "g " << (int)p[j+1] << endl;
              cout << "r " << (int)p[j+2] << endl;
              //cout << "a " << (int)p[j+4] << endl;
          }
          cout << endl;
      }

    cout << "continuous array with pointer" << endl;
      if (I.isContinuous()){
        uchar* p = I.data;
        for( int i =0; i < nCols*nRows; ++i){
          cout << (int)*p << " ";
          p++;
        }
      } else {
        cout << "not continuous" << endl;
      }

  //fileio
    I1 = imread( infile, 1 );
    imwrite( outfile, I1 );

  //highgui
    namedWindow( "sky", CV_WINDOW_AUTOSIZE );
    namedWindow( "gray", CV_WINDOW_AUTOSIZE );

    imshow( infile, I1 );
    imshow( "gray", I1 );

    waitKey(0);

  cout << "\nprofiling\n" << endl;
    d = (double)getTickCount();
    for(int i=0; i<1000; i++)
      i2++;
    d = ((double)getTickCount() - d)/getTickFrequency();
    cout << "seconds " << d << endl;

  cout << "error handling" << endl;
    CV_Assert(true);
    //EXCEPTION:
      //CV_Assert(false);

  //cvtColor( I1, gray_I1, CV_RGB2GRAY );

 return 0;
}
