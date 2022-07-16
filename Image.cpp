#include "Image.hpp"

Image::Image(int option){
    switch(option) {
        //-- Sharpen
        case 1:
            kernel[0][0] = 0;
            kernel[0][1] = -1;
            kernel[0][2] = 0;
            kernel[1][0] = -1;
            kernel[1][1] = 5;
            kernel[1][2] = -1;
            kernel[2][0] = 0;
            kernel[2][1] = -1;
            kernel[2][2] = 0;
        break;
        //-- edge Detection
        case 2:
            kernel[0][0] = -1;
            kernel[0][1] = -1;
            kernel[0][2] = -1;
            kernel[1][0] = -1;
            kernel[1][1] = 8;
            kernel[1][2] = -1;
            kernel[2][0] = -1;
            kernel[2][1] = -1;
            kernel[2][2] = -1;
        break; 
        //-- Gaussion Blur
        case 3:
            kernel[0][0] = 0.0625;
            kernel[0][1] = 0.125;
            kernel[0][2] = 0.0625;
            kernel[1][0] = 0.125;
            kernel[1][1] = 0.25;
            kernel[1][2] = 0.125;
            kernel[2][0] = 0.0625;
            kernel[2][1] = 0.125;
            kernel[2][2] = 0.0625;
        break;
        //  imageThresholding
        case 4:
        imageThresholding();
        break;
    }    
}

void Image::loadImage(string picturePath){
    image = imread(picturePath, 0);
    imshow("Input", image);
    cout << "input size : " << image.rows << "x" << image.cols << endl;
}

int  Image::imageThresholding(){
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
Mat Image::makebinary(Mat image, int threshold){
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

void Image::applyFilter() {
    Mat src((image.rows - 2),(image.cols - 2),image.type());
    int counter1, counter2;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            sumIndex = 0;
            for (int k = 0; k < 3; k++) {

                if (k == 0) {
                    counter1 = i;
                } else if (k == 1) {
                    counter1 = i + 1;
                } else if (k == 2) {
                    counter1 = i + 2;
                }
                for (int l = 0; l < 3; l++) {
                    if (l == 0) {
                        counter2 = j;
                    } else if (l == 1) {
                        counter2 = j + 1;
                    } else if (l == 2) {
                        counter2 = j + 2;
                    }
                    sumIndex += kernel[k][l] * image.at<uchar>(counter1, counter2);
                }
            }
            src.at<uchar>(i, j) = sumIndex;
        }
    }
    cout << "output size : " << src.rows << "x" << src.cols << endl;
    imshow("Output", src);
    waitKey(0);
    destroyAllWindows();
}