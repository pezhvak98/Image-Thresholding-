#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Configs.hpp"
class Image {
    private:
        Mat kernel;
        Mat image;
        Mat makebinary(Mat,int);
        Mat padding(Mat , int , int , string );
        Mat define_kernel(int , int , string );
        uchar sumIndex;
        double ratio = 1 ;
        int size = 3;
        int **arrKernel;
        int Mode;
        int ChoiceKernelMoD;
        int ChoiceConvolvemulti ;
        int PopKernel;
        int threshold = 10;

    public:
        Image(int);
        void loadImage(string);
        void applyFilter();
        void setKernel();
        void MenuKernel();
        void PopularKernel(); 
        void ZeroKernel();
        void convolve(Mat , Mat &, int , int , string , string );
        void ConvolveGuassianBlur();
        int imageThresholding();

};

#endif // IMAGE_HPP