#pragma once

#include <Eigen/Eigen>

#include "Image.h"

class Stereo
{
public:
	Stereo();
	~Stereo();

	Image* m_pLeftImage;
	Image* m_pRightImage;

	int m_pWindowSize = 15;

	Eigen::Matrix3f m_essMat;

	float getCorrPixel(int x, int y, float d)
	{
		Eigen::Vector3f p = d * m_essMat * Eigen::Vector3f(x, y, 1);
		return m_pRightImage->getPixel(p(0) / p(2), p(1) / p(2));
	}

	float getZNCC(int x, int y, float d)
	{
		float si = 0;
		float sj = 0;
		float sii = 0;
		float sjj = 0;
		float sij = 0;

		for (int i = x - m_pWindowSize; i <= x + m_pWindowSize; i++)
			for (int j = y - m_pWindowSize; j <= y + m_pWindowSize; j++)
			{
				float vLeft = m_pLeftImage->getPixel(i, j);
				float vRight = getCorrPixel(i, j, d);

				si += vLeft;
				sj += vRight;
				sii += vLeft * vLeft;
				sjj += vRight * vRight;
				sij += vLeft * vRight;
			}

		int n = (2 * m_pWindowSize + 1) * (2 * m_pWindowSize + 1);
		return (n * sij - si * sj) / sqrt((n * sii - si * si) * (n * sjj - sj * sj));
	}
};

