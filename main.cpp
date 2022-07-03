#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

Mat makebinary(Mat image, int threshold)
{
    Mat result(image.size(), CV_8UC1);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (image.at<uchar>(i, j) > threshold)
            {
                // Make pixel white
                result.at<uchar>(i, j) = 255;
            }
            else
            {
                // Make pixel black
                result.at<uchar>(i, j) = 0;
            }
        }
    }
    return result;
}

int main()
{
    Mat src = imread("mrl.jpg", 1);
    float kdata[] = {0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816,
                     0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816,
                     0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816,
                     0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816,
                     0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816,
                     0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816,
                     0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816, 0.02040816};
    Mat kernel(7, 7, CV_32F, kdata);
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
    imshow("original image", src);
    waitKey(0);

    // open the first webcam plugged in the computer
    VideoCapture camera(0);
    if (!camera.isOpened())
    {
        std::cerr << "ERROR: Could not open camera" << std::endl;
        return 1;
    }
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