#pragma once

#include <opencv2/opencv.hpp>

class Image
{
public:
	Image();
	~Image();

	enum ImageType {IMAGE, DIFF_X, DIFF_Y};

	void loadImage(const char * fileDir);
	float getPixel(float x, float y, ImageType type = IMAGE);

	int getCol()
	{
		return m_cols;
	}

	int getRow()
	{
		return m_rows;
	}

	cv::Mat_<uchar> m_image;
	cv::Mat_<float> m_diffX;
	cv::Mat_<float> m_diffY;

	

private:
	int m_cols = 0;
	int m_rows = 0;

	static float getInterP(float val0, float val1, float ratio)
	{
		return val0 + ratio * (val1 - val0);
	}
};

