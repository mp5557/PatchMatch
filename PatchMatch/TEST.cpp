#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>  

#include "Image.h"

int main()
{
	Image image;
	image.loadImage("view1.png");

	cv::Mat dst;
	dst.create(image.m_image.size(), CV_8UC1);
	int cx = image.getRow() / 2;
	int cy = image.getCol() / 2;
	float scale = 0.5;
	for (int i = 0; i < image.getRow(); i++)
		for (int j = 0; j < image.getCol(); j++)
		{
			float dx = (i - cx) / scale;
			float dy = (j - cy) / scale;
			dst.at<uchar>(i, j) = image.getPixel(cx + dx, cy + dy);
		}

	const char* name = "dst";
	cv::namedWindow(name, CV_WINDOW_NORMAL);
	cv::imshow(name, dst);

	const char* nameS = "src";
	cv::namedWindow(nameS, CV_WINDOW_NORMAL);
	cv::imshow(nameS, image.m_image);

	cv::waitKey();


}