# Vison-Task

## Intro

Vision in robotics
Robot vision refers to the capability of a robot to visually perceive the environment and use this information for execution of various tasks. Visual feedback has been used extensively for robot navigation and obstacle avoidance.

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




### Kernel without padding 


Padding describes the addition of empty pixels around the edges of an image. The purpose of padding is to preserve the original size of an image when applying a convolutional filter and enable the filter to perform full convolutions on the edge pixels.
Stride in the context of convolutional neural networks describes the process of increasing the step size by which you slide a filter over an input image. With a stride of 2, you advance the filter by two pixels at each step.

In this post we will learn how padding and stride work in practice and why we apply them in the first place.
#### Why Do We Need Padding?

When performing a standard convolution operation, the image shrinks by a factor equivalent to the filter size plus one. If we take an image of width and height 6, and a filter of width and height 3, the image shrinks by the following factor.

6 - 3 +1 = 4

The reason for the shrinking image is that a 3×3 filter cannot slide all three of its columns over the first two horizontal pixels in the image. The same problem exists with regard to the rows and the vertical pixels.


<img width="356" alt="Screenshot-2021-12-03-at-09 46 05" src="https://user-images.githubusercontent.com/71558436/179375194-8ac5ca80-fb1b-4e16-8bc6-0bf194ff4c61.png">



There are only 4 steps left for the filter until it reaches the end of the image, both vertically and horizontally. As a consequence, the resulting image will only have 4×4 dimensions instead of 6×6. The general formula for calculating the shrinkage of the image dimensions m x m based on the kernel size f x f, can be calculated as follows:

( m × m )∗(f × f) = (m − f + 1)∗(m − f + 1)


#### This immediately entails two problems:

##### 1-If you perform multiple convolution operations consecutively, the final image might become vanishingly small because the image will shrink with every operation.
##### 2-Because you cannot slide the full filter over the edge pixels, you cannot perform full convolutions. As a result you will lose some information at the edges.


The problem becomes more pronounced as the size of the filter increases. If we use a 5 x 5 filter on the 6 x 6 image, we only have space for 2 convolutions.

To address these problems, we can apply padding.

#####  But we only implemented without padding in this program 


![image](https://user-images.githubusercontent.com/71558436/179375296-2a142dc6-764a-4ee8-b30d-c2eb8b7e25fb.png)



Each filter has different values for its kernel, which can be implemented by placing it in the kernel and dropping it on the image.

![image](https://user-images.githubusercontent.com/71558436/179375328-9ec24a8a-6ee8-4f8d-bd0b-9c3abf1bccb3.png)


According to the specific formula that I explained above, we create a storage matrix to put the new values obtained in it

![image](https://user-images.githubusercontent.com/71558436/179375370-a677dd9e-355f-4fd4-a84f-8438e86ea169.png)


In this part of the code, we iterate on the image. When we reach each pixel, we have a series of conditions so that the kernel falls on the image and is multiplied correctly.

For example  sharpen filter:

![image](https://user-images.githubusercontent.com/71558436/179375711-1c7160e9-35cf-4e8e-97c5-85a16effb662.png)
