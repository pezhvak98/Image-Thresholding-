#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>


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
    return result;
}

int imageThresholding()
 { 
    VideoCapture camera(0);

    Mat image;
    namedWindow("Binary", WINDOW_AUTOSIZE);
    int threshold = 10;
    createTrackbar("Threshold", "Binary", &threshold, 255);
    while (1)
    {
        camera >> image;
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        Mat binary = makebinary(gray, threshold);
        imshow("Binary", binary);
        char a = waitKey(33);
        if (a == 27)
        {
            break;
        }
    }
   return 0;
 }



 void Convolve()
 {
   Mat src = imread("helianthus-yellow-flower-pixabay_11863.png", 1);
    float kdata[] = 
    { 
                 1.5, 1.5, 1.5, 
                 1.5, 1.5, 1.5,
                 1.5,1.5, 1.5
                 };
    Mat kernel(3, 3, CV_32F, kdata);
    Mat dst((src.rows - kernel.rows + 1), (src.cols - kernel.cols + 1), src.type());

    const int dx = kernel.cols / 2;
    const int dy = kernel.rows / 2;

    for (int i = 0; i < src.rows; i++)
    {
        for (int j = 0; j < src.cols; j++)
        {
            float tmp = 0.0f;
            for (int k = 0; k < kernel.rows; k++)
            {
                for (int l = 0; l < kernel.cols; l++)
                {
                    int x = j - dx + l;
                    int y = i - dy + k;
                    if (x >= 0 && x < src.cols && y >= 0 && y < src.rows)
                        tmp += src.at<float>(y, x) * kernel.at<float>(k, l);
                }
            }
            dst.at<float>(i, j) = saturate_cast<float>(tmp);
        }
    }

    cout << "original image row " << src.rows << endl;
    cout << "original image col" << src.cols << endl;
    cout << "Convlove image  row" << dst.rows << endl;
    cout << "Convlove image col" << dst.cols << endl;
    imshow("Convlove image", dst);
    waitKey(0);
 }


void ShowMenu()
{
  int choice;
  char flag;
  cout<<"\nEnter your choice\n";
  cout<<"\n1 -> ImageThresholding\n";
  cout<<"\n2 -> Convlove\n";
  while (true)
  {
    cin>> choice;
    switch (choice)
    {
       case 1:
          imageThresholding();
          break;
       case 2:
          Convolve();
          break;

       default:
          break;
    }
    
    cout<<"\n Do you Want Continue n or y\n";
    cin>> flag;

    if (flag=='n' && flag=='N')
    {
      break;
    }
    

  }
  
}

int main()
{
  ShowMenu();
  return 0;
}


