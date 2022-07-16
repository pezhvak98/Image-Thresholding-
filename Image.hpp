#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "Configs.hpp"

class Image {
    private:
        Mat image;
        Mat makebinary(Mat,int);
        double kernel[3][3];
        double sumIndex;

    public:
        Image(int);
        void loadImage(string);
        void applyFilter();
        int imageThresholding();

};

#endif // IMAGE_HPP