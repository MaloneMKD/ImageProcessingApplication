#include "pch.h"
#include "Functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <filesystem>


Image Functions::readImage(const char fname[])
{
	int width, height, depth;

	// Get RGB Data
	unsigned char* data = stbi_load(fname, &width, &height, &depth, 3);

	Image retImg(height, width, depth);

	// Copy pixel data to image rgb vector
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			for (int channel = 0; channel < depth; channel++)
				retImg.setPixelValRGB(row, col, channel, data[(row * width + col) * depth + channel]);
		}
	}

	// Get Grayscale Data
	unsigned char* grayscaleData = stbi_load(fname, &width, &height, &depth, 1);
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
			retImg.setPixelVal(row, col, grayscaleData[row * width + col]);
	}

	stbi_image_free(data);
	stbi_image_free(grayscaleData);

	return retImg;
}

winrt::Windows::Foundation::IAsyncAction Functions::merge(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicAnd(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicNand(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicOr(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicXor(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::addition(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::subtraction(Image& im1, Image& im2, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::multiplication(Image& im, Image& imOut, int factor)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::linearContrast(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::histogramEqualization(Image& im, Image& imOut)
{
	co_return;
}

int Functions::calculateContrast(Image& im)
{
	return 0;
}

winrt::Windows::Foundation::IAsyncAction Functions::luminance(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::gaussFilter(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::smoothingFilter(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::sharpen(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::edgeDetect(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::robertFilter(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::prewittFilter(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::sobelFilter(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::laplacienConvo(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::erosion(Image& im, Image& imOut)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::hFlip(Image& im, Image& imOut)
{
	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);
	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			imOut.setPixelValRGB(i, j, 0, im.getPixelValRGB(i, im.m_cols - j - 1, 0));
			imOut.setPixelValRGB(i, j, 1, im.getPixelValRGB(i, im.m_cols - j - 1, 1));
			imOut.setPixelValRGB(i, j, 2, im.getPixelValRGB(i, im.m_cols - j - 1, 2));
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::vFlip(Image& im, Image& imOut)
{
	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);
	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			imOut.setPixelValRGB(i, j, 0, im.getPixelValRGB(im.m_rows - i - 1, j, 0));
			imOut.setPixelValRGB(i, j, 1, im.getPixelValRGB(im.m_rows - i - 1, j, 1));
			imOut.setPixelValRGB(i, j, 2, im.getPixelValRGB(im.m_rows - i - 1, j, 2));
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::rRotate(Image& im, Image& imOut)
{
	imOut.initialize(im.m_cols, im.m_rows, im.m_depth);
	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			imOut.setPixelValRGB(j, im.m_rows - i - 1, 0, im.getPixelValRGB(i, j, 0));
			imOut.setPixelValRGB(j, im.m_rows - i - 1, 1, im.getPixelValRGB(i, j, 1));
			imOut.setPixelValRGB(j, im.m_rows - i - 1, 2, im.getPixelValRGB(i, j, 2));
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::lRotate(Image& im, Image& imOut)
{
	imOut.initialize(im.m_cols, im.m_rows, im.m_depth);
	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			imOut.setPixelValRGB(im.m_cols - j - 1, i, 0, im.getPixelValRGB(i, j, 0));
			imOut.setPixelValRGB(im.m_cols - j - 1, i, 1, im.getPixelValRGB(i, j, 1));
			imOut.setPixelValRGB(im.m_cols - j - 1, i, 2, im.getPixelValRGB(i, j, 2));
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::otsuBinarization(Image& im, Image& imOut, int& thresholdOut)
{
	thresholdOut = getOtsuBinarizationThreshold(im);
	thresholdVal(thresholdOut, im, imOut);
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::brightness(Image& im, Image& imOut, int level)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::filtering(Image& im, Image& imOut, double r, double g, double b)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::linearContrastSaturation(Image& im, Image& imOut, int sMin, int sMax)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::scalingNN(Image& im, Image& imOut, double xscale, double yscale)
{
	co_return;
}

// ======================== HELPER FUNCTIONS ========================

void Functions::thresholdVal(int threashold, Image& im, Image& outImg)
{
	outImg.initialize(im.m_rows, im.m_cols, im.m_depth);
	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			int val = im.getPixelVal(i, j) > threashold ? 255 : 0;
			outImg.setPixelVal(i, j, val);
		}
	}
}

int Functions::getOtsuBinarizationThreshold(Image& im)
{
	std::vector<float> histogram(256, 0);
	float sum = 0;

	// Get histogram
	for (int i = 0; i < im.m_pixelData.size(); i++)
		histogram[im.m_pixelData[i]]++;

	// Calculate global mean
	for (int i = 0; i < 256; i++)
		sum += i * histogram[i];

	// Calculate
	float sumB = 0.0f;
	float wB = 0.0f;
	float wF = 0.0f;
	float varMax = 0.0f;
	int threshold = 0;

	for (int i = 0; i < 256; i++) // Potential threshold
	{
		wB += histogram[i];
		if (wB == 0)
			continue;

		wF = (im.m_rows * im.m_cols) - wB;
		if (wF == 0)
			break;

		sumB += (float)(i * histogram[i]);
		float uB = sumB / wB;
		float uF = ((float)sum - sumB) / wF;

		float varBetween = wB * wF * (uB - uF) * (uB - uF);

		if (varBetween > varMax)
		{
			varMax = varBetween;
			threshold = i;
		}
	}
	return threshold;
}
