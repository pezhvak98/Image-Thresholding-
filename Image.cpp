#include "Image.hpp"

Image::Image(int option){

    switch(option) {
        //-- Kernel Menu
        case 1:
            MenuKernel();
            break;
        //  imageThresholding
        case 2:
            imageThresholding();
            break;
    }   

}

void Image::MenuKernel(){

    cout << "\n Enter Your Choice \n";
    cout << " 1 -> Popular Kernels\n 2-> Manual Set Kernel \n 3-> ConvolveGuassianBlur \n";
    cin >> ChoiceKernelMoD;
    switch (ChoiceKernelMoD)
    {
    case 1:
        PopularKernel();
        break;
    case 2:
        setKernel();
        break;
    case 3:
        ConvolveGuassianBlur();
        break;
    default:
        cout <<"\n Your Number is false \n";
        break;
    }

}


Mat Image::padding(Mat img, int k_width, int k_height, string type){

		Mat scr;
		img.convertTo(scr, CV_64FC1);
		int pad_rows, pad_cols;
		pad_rows = (k_height - 1) / 2;
		pad_cols = (k_width - 1) / 2;
		Mat pad_image(Size(scr.cols + 2 * pad_cols, scr.rows + 2 * pad_rows), CV_64FC1, Scalar(0));
		scr.copyTo(pad_image(Rect(pad_cols, pad_rows, scr.cols, scr.rows)));
		// mirror padding
		if (type == "mirror")
		{
			for (int i = 0; i < pad_rows; i++)
			{
				scr(Rect(0, pad_rows - i, scr.cols, 1)).copyTo(pad_image(Rect(pad_cols, i, scr.cols, 1)));
				scr(Rect(0, (scr.rows - 1) - pad_rows + i, scr.cols, 1)).copyTo(pad_image(Rect(pad_cols,
					(pad_image.rows - 1) - i, scr.cols, 1)));
			}

			for (int j = 0; j < pad_cols; j++)
			{
				pad_image(Rect(2 * pad_cols - j, 0, 1, pad_image.rows)).copyTo(pad_image(Rect(j, 0, 1, pad_image.rows)));
				pad_image(Rect((pad_image.cols - 1) - 2 * pad_cols + j, 0, 1, pad_image.rows)).
					copyTo(pad_image(Rect((pad_image.cols - 1) - j, 0, 1, pad_image.rows)));
			}

			return pad_image;
		}
		// replicate padding
		else if (type == "replicate")
		{
			for (int i = 0; i < pad_rows; i++)
			{
				scr(Rect(0, 0, scr.cols, 1)).copyTo(pad_image(Rect(pad_cols, i, scr.cols, 1)));
				scr(Rect(0, (scr.rows - 1), scr.cols, 1)).copyTo(pad_image(Rect(pad_cols, 
					(pad_image.rows - 1) - i, scr.cols, 1)));
			}

			for (int j = 0; j < pad_cols; j++)
			{
				pad_image(Rect(pad_cols, 0, 1, pad_image.rows)).copyTo(pad_image(Rect(j, 0, 1, pad_image.rows)));
				pad_image(Rect((pad_image.cols - 1) - pad_cols, 0, 1, pad_image.rows)).
					copyTo(pad_image(Rect((pad_image.cols - 1) - j, 0, 1, pad_image.rows)));
			}
			// zero padding
			return pad_image;
		}
		else
		{
			return pad_image;
		}

}


Mat Image::define_kernel(int k_width, int k_height, string type){

		// box kernel
		if (type == "box")
		{
			Mat kernel(k_height, k_width, CV_64FC1, Scalar(1.0 / (k_width * k_height)));
			return kernel;
		}
		// gaussian kernel
		else if (type == "gaussian")
		{
			// I will assume k = 1 and sigma = 1
			int pad_rows = (k_height - 1) / 2;
			int pad_cols = (k_width - 1) / 2;
			Mat kernel(k_height, k_width, CV_64FC1);
			for (int i = -pad_rows; i <= pad_rows; i++)
			{
				for (int j = -pad_cols; j <= pad_cols; j++)
				{
					kernel.at<double>(i + pad_rows, j + pad_cols) = exp(-(i*i + j*j) / 2.0);
				}
			}
			kernel = kernel / sum(kernel);
			return kernel;
		}

}

void Image::convolve(Mat scr, Mat &dst, int k_w, int k_h, string paddingType, string filterType){

		Mat pad_img, kernel;
		pad_img = padding(scr, k_w, k_h, paddingType);
		kernel = define_kernel(k_w, k_h, filterType);

		Mat output = Mat::zeros(scr.size(), CV_64FC1);

		for (int i = 0; i < scr.rows; i++)
		{
			for (int j = 0; j < scr.cols; j++)
			{
				output.at<double>(i, j) = sum(kernel.mul(pad_img(Rect(j, i, k_w, k_h)))).val[0];
			}
		}
		output.convertTo(dst, CV_8UC1); //IplImage: IPL_DEPTH_8U Mat: CV_8UC1, CV_8UC2, CV_8UC3, CV_8UC4
        
}

void Image::ConvolveGuassianBlur(){

    cout<< "you have selected ConvolveGuassianBlur to blur image : \n";
    Mat img, dst;
    // Load the image
    img = imread("pic.png", 0);   
    imshow("real",img);
    Mat kernel;
    int k_w = 19;  // kernel width
    int k_h = 19;  // kernel height
    convolve(img, dst, k_w, k_h, "mirror", "box");
    namedWindow("dst", WINDOW_AUTOSIZE);     
    imshow("dst", dst);     
    waitKey(0);

}

	
void Image::setKernel(){

    initial_value = 1;
    ChoiceConvolvemulti = 1;
    matrix.resize(size, vector<int>(size, initial_value));
    cout << "\n enter Ratio \n";
    cin >> ratio;
}

void Image::PopularKernel(){

    size = 3;
    ChoiceConvolvemulti = -1;
    cout << "\n 1->Identity Kernel\n 2-> Edge detection \n 3-> Sharpen Kernel \n 4-> Box Blur \n";
    cin >> PopKernel;
    switch (PopKernel)
    {
    case 1:
        kernel = (Mat_<uchar>(3, 3) <<   0, 0 , 0,
                                         0, 1 , 0,
                                         0, 0 , 0);  
        break;
    case 2:
        kernel = (Mat_<uchar>(3, 3) <<   -1 , -1 , -1,
                                         -1 ,  8 , -1,
                                         -1 , -1 , -1);
        break;
    case 3:
        kernel = (Mat_<uchar>(3, 3) <<    0 , -1 ,  0,
                                         -1 ,  5 , -1,
                                          0 , -1 ,  0);
        break;                                           
    case 4:
        kernel = (Mat_<uchar>(3, 3) <<    1 ,  1 ,  1,
                                          1 ,  1 ,  1,
                                          1 ,  1 ,  1);
        ratio = (double) 1/9;
        break;                                        
    default:
        break;
    }

}

int Image::imageThresholding(){

    VideoCapture camera(0);
    Mat image;
    namedWindow("Binary", WINDOW_AUTOSIZE);
    int threshold = size;
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


void Image::loadImage(string picturePath){

    image = imread(picturePath, 0);
    cout << "input size : " << image.rows << "x" << image.cols << endl;

}

void Image::applyFilter() {

    Mat src((image.rows - size + 1),(image.cols - size + 1),image.type());
    int dx = size / 2;
    int dy = size / 2;
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            sumIndex = 0;
            if(ChoiceConvolvemulti == 1){
             for (int k = 0; k < matrix.size(); k++) {
                    for (int l = 0; l < matrix[k].size(); l++) {
                
                                 int x = j - dx + l;
                                 int y = i - dy + k;
                                 if (x >= 0 && x < src.cols && y >= 0 && y < src.rows){
                                 sumIndex += matrix[k][l]* image.at<uchar>(y, x) * ratio ;
                    }
                }
            }
        
        }
        if (ChoiceConvolvemulti == -1)
        {
                            
             for (int k = 0; k < size; k++) {
                    for (int l = 0; l < size; l++) {
                           int x = j - dx + l;
                            int y = i - dy + k;
                             if (x >= 0 && x < src.cols && y >= 0 && y < src.rows){
                                sumIndex += kernel.at<uchar>(k,l) * image.at<uchar>(y, x) * ratio ;
                
                     }
                }
                    
          }
        }
        src.at<uchar>(i, j) = saturate_cast<uchar>(sumIndex) ;
        
        }
    }
    cout << "output size : " << src.rows << "x" << src.cols << endl;
    imshow("Output", src);
    waitKey(0);
    destroyAllWindows();

}



