#pragma once

#include "Image.h"

#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>

class Functions
{
public:
	static Image readImage(const char fname[]);
	static winrt::Windows::Foundation::IAsyncAction merge(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction logicAnd(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction logicNand(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction logicOr(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction logicXor(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction addition(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction subtraction(Image& im1, Image& im2, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction multiplication(Image& im, Image& imOut, int factor);

	static winrt::Windows::Foundation::IAsyncAction linearContrast(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction histogramEqualization(Image& im, Image& imOut);
	static int  calculateContrast(Image& im);
	static winrt::Windows::Foundation::IAsyncAction luminance(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction gaussFilter(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction smoothingFilter(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction sharpen(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction edgeDetect(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction robertFilter(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction prewittFilter(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction sobelFilter(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction laplacienConvo(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction erosion(Image& im, Image& imOut);

	static winrt::Windows::Foundation::IAsyncAction hFlip(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction vFlip(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction rRotate(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction lRotate(Image& im, Image& imOut);
	static winrt::Windows::Foundation::IAsyncAction otsuBinarization(Image& im, Image& imOut, int& thresholdOut);

	static winrt::Windows::Foundation::IAsyncAction brightness(Image& im, Image& imOut, int level);
	static winrt::Windows::Foundation::IAsyncAction filtering(Image& im, Image& imOut, double r, double g, double b);
	static winrt::Windows::Foundation::IAsyncAction linearContrastSaturation(Image& im, Image& imOut, int sMin, int sMax);
	static winrt::Windows::Foundation::IAsyncAction scalingNN(Image& im, Image& imOut, double xscale, double yscale);

	// Error reporting
	bool m_bError = false;
	winrt::hstring m_errorString = L"";

private:
	static int getOtsuBinarizationThreshold(Image& im);
	static void thresholdVal(int threshold, Image& im, Image& outImg);
};

