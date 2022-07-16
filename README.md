# Vison-Task

## Intro
**We implemented two operations in this project**  
**1- imageThresholding**
**2- image Filters and Kernel Convolution Visually** 

## ImageThresholding

### what is image thresholding?
thresholding is the simplest method of segmenting images. From a grayscale image, thresholding can be used to create binary images.

### How it work
The input to a thresholding operation is typically a grayscale or color image. In the simplest implementation, the output is a binary image representing the segmentation. Black pixels correspond to background and white pixels correspond to foreground (or vice versa). In simple implementations, the segmentation is determined by a single parameter known as the intensity threshold. In a single pass, each pixel in the image is compared with this threshold. If the pixel's intensity is higher than the threshold, the pixel is set to, say, white in the output. If it is less than the threshold, it is set to black.

![image](https://user-images.githubusercontent.com/71558436/179368125-abae01fd-ed5a-48d1-913c-90358729e8ed.png)

1-First, we create a matrix and receive the image in grayscale format
2-We send the image to the makebinary function to perform operations on it
