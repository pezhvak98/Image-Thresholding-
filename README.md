# Image-Thresholding-
 Basic thresholding of an image using OpenCV library with trackbar


## What is the threshold of an image?
Image thresholding is a simple form of image segmentation. It is a way to create a binary image from grayscale or full-color image. This is typically done to separate "object" or foreground pixels from background pixels to aid in image processing.

## Basic requirements

In this project, we use the [OpenCV library](https://opencv.org/releases/), so in the first step, we have to install it completely
Then the **include_path** must be added to the our project so that the library is fully known

## Threshold Roadmap

First, we have to convert the input image to a gray channel and then scroll it pixel by pixel and compare it with the threshold number, if the number is towards 255 it will be a white pixel and if it is towards 0 it will be a pixel. Be black
Finally, we design a trackbar with a maximum value of 255 so that the user can find the variable number without re-running the program to achieve the best result.
### result :
![thresholding ](/Readme-asset/shot.png?raw=true "thresholding result image")

## Make and Run 

You can also run the program by creating a MakeFile, but the suggested way to run the program is .
### make:

    g++ main.cpp -o main `pkg-config --cflags --libs opencv4`
    
### Run:

    ./main
