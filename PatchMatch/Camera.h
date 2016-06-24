#pragma once

#include <vector>

#include <Eigen\Eigen>

#include "Image.h"


class Camera
{
public:
	Camera();
	~Camera();

	Image* m_pImage;

	float getPixel(float x, float y)
	{
		return m_pImage->getPixel(x, y);
	}

	float getProjPixel(float x, float y, const Camera& camera, float depth)
	{

	}

	Eigen::Matrix3f m_projMat;
};

