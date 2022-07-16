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

![image](https://user-images.githubusercontent.com/71558436/179369593-e6f64db1-ebe7-43f2-bd35-d9f493c43fd3.png)

3-We get the value, if the pixel value is less than it, the pixel will be black, if it is more, it will be white

## image Filters and Kernel Convolution Visually


### what is kernel?
In image processing, a kernel, convolution matrix, or mask is a small matrix used for blurring, sharpening, embossing, edge detection, and more. This is accomplished by doing a convolution between the kernel and an image.




![1_Eai425FYQQSNOaahTXqtgg](https://user-images.githubusercontent.com/71558436/179374841-3108779a-d9f5-4355-91d6-fce49dec451e.gif)

For example, the kernel used above is useful for sharpening the image. But what is so special about this kernel?? Consider the two input image arrangements as shown in the example below. For the first image, the center value is 3*5 + 2*-1 + 2*-1 + 2*-1 + 2*-1 = 7. The value 3 got increased to 7. For the second image, the output is 1*5+ 2*-1 + 2*-1 + 2*-1 + 2*-1 = -3. The value 1 got decreased to -3. Clearly, the contrast between 3 and 1 is increased to 7 and -3, which will in turn sharpen the image.

#### But this example had padding


### Kernel without padding 


Padding describes the addition of empty pixels around the edges of an image. The purpose of padding is to preserve the original size of an image when applying a convolutional filter and enable the filter to perform full convolutions on the edge pixels.
Stride in the context of convolutional neural networks describes the process of increasing the step size by which you slide a filter over an input image. With a stride of 2, you advance the filter by two pixels at each step.

In this post we will learn how padding and stride work in practice and why we apply them in the first place.
Why Do We Need Padding?
When performing a standard convolution operation, the image shrinks by a factor equivalent to the filter size plus one. If we take an image of width and height 6, and a filter of width and height 3, the image shrinks by the following factor.

6 - 3 +1 =4
6−3+1=4
The reason for the shrinking image is that a 3×3 filter cannot slide all three of its columns over the first two horizontal pixels in the image. The same problem exists with regard to the rows and the vertical pixels.



