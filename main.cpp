/*
Coded by Mehmet Aygun
03.04.2015
*/


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"   
#include <opencv2/core/core.hpp>
 
  
#include <string>

using namespace cv;



int main( int argc, const char** argv )
{
    if (argc < 2){
        cout << "Please give the path of test image like :  ./app /home/Desktop/test.jpg" << endl ;
        return -1; 
    }

    CascadeClassifier face_cascade("kiss_cascade.xml"); // load cascade
    if ( face_cascade.empty() ) {
        cout << "Error loading cascade file" << endl ;
        return -1; 
    }

    string path = argv[1];

    Mat frame = imread(path); // load example image
    if ( frame.empty() ) {
        cout << "Error loading image file" << endl;
        return -1; 
    }

    Mat frame_gray;
    cvtColor(frame,frame_gray,COLOR_RGB2GRAY); // convert to grayscale
	//equalizeHist( frame_gray, frame_gray );
	GaussianBlur( frame_gray, frame_gray, Size( 7, 7 ), 0.8,0.8 ); // apply blur for noises

    std::vector<Rect> kisses;
    face_cascade.detectMultiScale( frame_gray, kisses, 1.5, 4, 0|1, Size(40, 24) ); // try to find kisses

    for (unsigned int i=0; i<kisses.size(); ++i ) {
        rectangle( frame, kisses[i], Scalar( 255, 0, 0 ), 2 );
    }
    imshow("kiss-detect",frame);
    waitKey();
    return 0;
}
