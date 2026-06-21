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

void Functions::merge(Image& im1, Image& im2)
{
}

void Functions::logicAnd(Image& im1, Image& im2)
{
}

void Functions::logicNand(Image& im1, Image& im2)
{
}

void Functions::logicOr(Image& im1, Image& im2)
{
}

void Functions::logicXor(Image& im1, Image& im2)
{
}

void Functions::addition(Image& im1, Image& im2)
{
}

void Functions::subtraction(Image& im1, Image& im2)
{
}

void Functions::multiplication(Image& im, int factor)
{
}

void Functions::displayRgb(Image& im)
{
}

void Functions::displayGray(Image& im)
{
}

void Functions::linearContrast(Image& im)
{
}

void Functions::histogramEqualization(Image& im)
{
}

int Functions::calculateContrast(Image& im)
{
	return 0;
}

void Functions::luminance(Image& im)
{
}

void Functions::gaussFilter(Image& im)
{
}

void Functions::smoothingFilter(Image& im)
{
}

void Functions::sharpen(Image& im)
{
}

void Functions::edgeDetect(Image& im)
{
}

void Functions::robertFilter(Image& im)
{
}

void Functions::prewittFilter(Image& im)
{
}

void Functions::sobelFilter(Image& im)
{
}

void Functions::laplacienConvo(Image& im)
{
}

void Functions::erosion(Image& im)
{
}

void Functions::hFlip(Image& im)
{
}

void Functions::vFlip(Image& im)
{
}

void Functions::rRotate(Image& im)
{
}

void Functions::lRotate(Image& im)
{
}

void Functions::brightness(Image& im, int level)
{
}

void Functions::filtering(Image& im, double r, double g, double b)
{
}

void Functions::linearContrastSaturation(Image& im, int sMin, int sMax)
{
}

void Functions::scalingNN(Image& im, double xscale, double yscale)
{
}
