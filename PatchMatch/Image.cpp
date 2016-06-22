#include <math.h>

#include "Image.h"


Image::Image()
{
}


Image::~Image()
{
}

void Image::loadImage(const char * fileDir)
{
	m_image = cv::imread(fileDir, CV_LOAD_IMAGE_GRAYSCALE);
	m_cols = m_image.cols;
	m_rows = m_image.rows;

	cv::Sobel(m_image, m_diffX, CV_32FC1, 1, 0);
	cv::Sobel(m_image, m_diffY, CV_32FC1, 0, 1);
}

float Image::getPixel(float x, float y, ImageType type /*= IMAGE*/)
{
	int x_low = floor(x);
	int x_high = ceil(x);
	int y_low = floor(y);
	int y_high = ceil(y);

	if (x_low < 0 || x_high >= m_rows || y_low < 0 || y_high >= m_cols)
		return 0;

	float v00, v01, v10, v11;
	switch (type)
	{
	case IMAGE:
		v00 = m_image(x_low, y_low);
		v10 = m_image(x_high, y_low);
		v01 = m_image(x_low, y_high);
		v11 = m_image(x_high, y_high);
		break;
	case DIFF_X:
		v00 = m_diffX(x_low, y_low);
		v10 = m_diffX(x_high, y_low);
		v01 = m_diffX(x_low, y_high);
		v11 = m_diffX(x_high, y_high);
		break;
	case DIFF_Y:
		v00 = m_diffY(x_low, y_low);
		v10 = m_diffY(x_high, y_low);
		v01 = m_diffY(x_low, y_high);
		v11 = m_diffY(x_high, y_high);
		break;
	}

	float v0 = getInterP(v00, v01, y - y_low);
	float v1 = getInterP(v10, v11, y - y_low);
	return getInterP(v0, v1, x - x_low);
}
