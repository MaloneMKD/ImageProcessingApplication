#include "pch.h"
#include "Functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <filesystem>
#include <numeric>

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
	// Images must have the same depth rows and columns
	if (im1.m_depth != im2.m_depth || im1.m_rows != im2.m_rows || im1.m_cols != im2.m_cols)
		co_return;

	int pixel = 0;
	int threshold = 0;
	Image binImg1, binImg2;
	otsuBinarization(im1, binImg1, threshold);
	otsuBinarization(im2, binImg2, threshold);
	imOut.initialize(im1.m_rows, im1.m_cols, im1.m_depth);

	for (int i = 0; i < im1.m_rows; i++)
	{
		for (int j = 0; j < im1.m_cols; j++)
		{
			pixel = binImg1.getPixelVal(i, j) && binImg2.getPixelVal(i, j);
			int val = (pixel == 1) ? 255 : 0; // 255 && 255 = 1 and 255 && 0 = 0
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicNand(Image& im1, Image& im2, Image& imOut)
{
	// Images must have the same depth rows and columns
	if (im1.m_depth != im2.m_depth || im1.m_rows != im2.m_rows || im1.m_cols != im2.m_cols)
		co_return;

	int pixel = 0;
	int threshold = 0;
	Image binImg1, binImg2;
	otsuBinarization(im1, binImg1, threshold);
	otsuBinarization(im2, binImg2, threshold);
	imOut.initialize(im1.m_rows, im1.m_cols, im1.m_depth);

	for (int i = 0; i < im1.m_rows; i++)
	{
		for (int j = 0; j < im1.m_cols; j++)
		{
			pixel = !(binImg1.getPixelVal(i, j) && binImg2.getPixelVal(i, j));
			int val = (pixel == 1) ? 255 : 0; // 255 && 255 = 1 and 255 && 0 = 0
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicOr(Image& im1, Image& im2, Image& imOut)
{
	// Images must have the same depth rows and columns
	if (im1.m_depth != im2.m_depth || im1.m_rows != im2.m_rows || im1.m_cols != im2.m_cols)
		co_return;

	int pixel = 0;
	int threshold = 0;
	Image binImg1, binImg2;
	otsuBinarization(im1, binImg1, threshold);
	otsuBinarization(im2, binImg2, threshold);
	imOut.initialize(im1.m_rows, im1.m_cols, im1.m_depth);

	for (int i = 0; i < im1.m_rows; i++)
	{
		for (int j = 0; j < im1.m_cols; j++)
		{
			pixel = binImg1.getPixelVal(i, j) || binImg2.getPixelVal(i, j);
			int val = (pixel == 1) ? 255 : 0; // 255 && 255 = 1 and 255 && 0 = 0
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::logicXor(Image& im1, Image& im2, Image& imOut)
{
	// Images must have the same depth rows and columns
	if (im1.m_depth != im2.m_depth || im1.m_rows != im2.m_rows || im1.m_cols != im2.m_cols)
		co_return;

	int pixel = 0;
	int threshold = 0;
	Image binImg1, binImg2;
	otsuBinarization(im1, binImg1, threshold);
	otsuBinarization(im2, binImg2, threshold);
	imOut.initialize(im1.m_rows, im1.m_cols, im1.m_depth);

	for (int i = 0; i < im1.m_rows; i++)
	{
		for (int j = 0; j < im1.m_cols; j++)
		{
			pixel = (binImg1.getPixelVal(i, j) && !(binImg2.getPixelVal(i, j))) || (binImg2.getPixelVal(i, j) && !(binImg1.getPixelVal(i, j)));
			int val = (pixel == 1) ? 255 : 0; // 255 && 255 = 1 and 255 && 0 = 0
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::addition(Image& im1, Image& im2, Image& imOut)
{
	// Images must have the same depth rows and columns
	if (im1.m_depth != im2.m_depth || im1.m_rows != im2.m_rows || im1.m_cols != im2.m_cols)
		co_return;

	int pixel = 0;
	int threshold = 0;
	Image binImg1, binImg2;
	otsuBinarization(im1, binImg1, threshold);
	otsuBinarization(im2, binImg2, threshold);
	imOut.initialize(im1.m_rows, im1.m_cols, im1.m_depth);

	for (int i = 0; i < im1.m_rows; i++)
	{
		for (int j = 0; j < im1.m_cols; j++)
		{
			pixel = binImg1.getPixelVal(i, j) + binImg2.getPixelVal(i, j);
			int val = min(pixel, 255);
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::subtraction(Image& im1, Image& im2, Image& imOut)
{
	// Images must have the same depth rows and columns
	if (im1.m_depth != im2.m_depth || im1.m_rows != im2.m_rows || im1.m_cols != im2.m_cols)
		co_return;

	int pixel = 0;
	int threshold = 0;
	Image binImg1, binImg2;
	otsuBinarization(im1, binImg1, threshold);
	otsuBinarization(im2, binImg2, threshold);
	imOut.initialize(im1.m_rows, im1.m_cols, im1.m_depth);

	for (int i = 0; i < im1.m_rows; i++)
	{
		for (int j = 0; j < im1.m_cols; j++)
		{
			pixel = binImg1.getPixelVal(i, j) - binImg2.getPixelVal(i, j);
			int val = max(pixel, 0);
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::multiplication(Image& im, Image& imOut, int factor)
{
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::linearContrast(Image& im, Image& imOut)
{
	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);

	int mini = *std::min_element(im.m_pixelData.begin(), im.m_pixelData.end());
	int maxi = *std::max_element(im.m_pixelData.begin(), im.m_pixelData.end());
	int pixel = 0;
	int val = 0;

	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			pixel = im.getPixelVal(i, j);
			val = 255 * (pixel - mini) / (maxi - mini);
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::histogramEqualization(Image& im, Image& imOut)
{
	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);

	int totalPixels = im.m_pixelData.size();
	int max = 255;

	// Get histogram	
	std::vector<float> histogram(256, 0);
	for (int i = 0; i < im.m_pixelData.size(); i++)
		histogram[im.m_pixelData[i]]++;

	// Get Probability Distribution Function
	std::vector<float> pdf(histogram.size(), 0);
	for (int i = 0; i < histogram.size(); i++)
		pdf[i] = histogram[i] / totalPixels;

	// Get Cumulative Distrinution Function and LUT
	std::vector<float> cdf(histogram.size());
	std::vector<float> LUT(histogram.size());
	cdf[0] = pdf[0];
	imOut.m_pixelData[0] = pdf[0];

	for (int i = 1; i < histogram.size(); i++)
	{
		cdf[i] = cdf[i - 1] + pdf[i];
		LUT[i] = std::round(cdf[i] * max);
	}

	// Apply LUT to image
	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
			imOut.setPixelVal(i, j, LUT[im.getPixelVal(i, j)]);
	}

	co_return;
}

int Functions::calculateContrast(Image& im)
{
	int contrast = 0;
	int mini = *std::min_element(im.m_pixelData.begin(), im.m_pixelData.end());
	int maxi = *std::max_element(im.m_pixelData.begin(), im.m_pixelData.end());
	contrast = maxi - mini;

	return contrast;
}

int Functions::luminance(Image& im)
{
	double sum = std::accumulate(im.m_pixelData.begin(), im.m_pixelData.end(), 0);
	double lum = sum / im.m_pixelData.size();
	return lum;
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
	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);
	int pixel = 0;
	int val = 0;

	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
			imOut.setPixelVal(i, j, max(0, min(255, im.getPixelVal(i, j) + level)));
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::filtering(Image& im, Image& imOut, double r, double g, double b)
{
	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);
	int val = 0;
	int pixel = 0;

	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			imOut.setPixelValRGB(i, j, 0, min(255, im.getPixelValRGB(i, j, 0) * r));
			imOut.setPixelValRGB(i, j, 1, min(255, im.getPixelValRGB(i, j, 1) * g));
			imOut.setPixelValRGB(i, j, 2, min(255, im.getPixelValRGB(i, j, 2) * b));
		}
	}

	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::linearContrastSaturation(Image& im, Image& imOut, int sMin, int sMax)
{
	auto minPixel = *std::min_element(im.m_pixelData.begin(), im.m_pixelData.end());
	auto maxPixel = *std::max_element(im.m_pixelData.begin(), im.m_pixelData.end());
	if ((sMin > sMax) || sMin < minPixel || sMax > maxPixel)
		co_return; // Report invalid saturation values

	imOut.initialize(im.m_rows, im.m_cols, im.m_depth);

	int pixel = 0;
	int val = 0;

	for (int i = 0; i < im.m_rows; i++)
	{
		for (int j = 0; j < im.m_cols; j++)
		{
			pixel = im.getPixelVal(i, j);
			val = 255 * (pixel - sMin) / (sMax - sMin);
			imOut.setPixelVal(i, j, val);
		}
	}
	co_return;
}

winrt::Windows::Foundation::IAsyncAction Functions::scalingNN(Image& im, Image& imOut, double xscale, double yscale)
{
	int destW = im.m_cols * xscale;
	int destH = im.m_rows * yscale;

	imOut.initialize(destH, destW, im.m_depth);

	for (int i = 0; i < destH; i++)
	{
		for (int j = 0; j < destW; j++)
		{
			imOut.setPixelValRGB(i, j, 0, im.getPixelValRGB(i / yscale, j / xscale, 0));
			imOut.setPixelValRGB(i, j, 1, im.getPixelValRGB(i / yscale, j / xscale, 1));
			imOut.setPixelValRGB(i, j, 2, im.getPixelValRGB(i / yscale, j / xscale, 2));
		}
	}
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
