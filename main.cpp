#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat makebinary(Mat image, int threshold){

    Mat result(image.size(),CV_8UC1);
    for(int i = 0 ; i < image.rows ; i++){
        for(int j = 0 ; j < image.cols ; j++){
            if(image.at<uchar>(i,j)>threshold){
                result.at<uchar>(i,j)=255;	//Make pixel white
            }	
			else{
                result.at<uchar>(i,j)=0;	//Make pixel black
            }
				
        }
    }
}



int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
