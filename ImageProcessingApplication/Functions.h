#pragma once

#include "Image.h"

class Functions
{
public:
	static Image readImage(const char fname[]);
	static void merge(Image& im1, Image& im2);
	static void logicAnd(Image& im1, Image& im2);
	static void logicNand(Image& im1, Image& im2);
	static void logicOr(Image& im1, Image& im2);
	static void logicXor(Image& im1, Image& im2);
	static void addition(Image& im1, Image& im2);
	static void subtraction(Image& im1, Image& im2);
	static void multiplication(Image& im, int factor);

	static void displayRgb(Image& im);
	static void displayGray(Image& im);
	static void linearContrast(Image& im);
	static void histogramEqualization(Image& im);
	static int  calculateContrast(Image& im);
	static void luminance(Image& im);
	static void gaussFilter(Image& im);
	static void smoothingFilter(Image& im);
	static void sharpen(Image& im);
	static void edgeDetect(Image& im);
	static void robertFilter(Image& im);
	static void prewittFilter(Image& im);
	static void sobelFilter(Image& im);
	static void laplacienConvo(Image& im);
	static void erosion(Image& im);

	static void hFlip(Image& im);
	static void vFlip(Image& im);
	static void rRotate(Image& im);
	static void lRotate(Image& im);

	static void brightness(Image& im, int level);
	static void filtering(Image& im, double r, double g, double b);
	static void linearContrastSaturation(Image& im, int sMin, int sMax);
	static void scalingNN(Image& im, double xscale, double yscale);
};

