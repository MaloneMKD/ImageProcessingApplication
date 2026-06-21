#include "pch.h"
#include "Image.h"

Image::Image() : m_rows(0), m_cols(0), m_depth(0)
{
}

Image::Image(int numRows, int numCols, int depth): m_rows(numRows), m_cols(numCols), m_depth(depth)
{
	// Initialize the pixel data vector with the appropriate size
	m_pixelData.resize(m_rows * m_cols, 0);

	// Initialize the 3D pixel data vector with the appropriate size
	m_pixelDataRGB.resize(m_rows * m_cols * m_depth, 0);
}

uint8_t Image::getPixelVal(int row, int col)
{
	int index = (row * m_cols) + col;
	return m_pixelData[index];
}

void Image::setPixelVal(int row, int col, uint8_t val)
{
	int index = (row * m_cols) + col;
	m_pixelData[index] = val;
}

uint8_t Image::getPixelValRGB(int row, int col, int depth)
{
	int index = ((row * m_cols) + col) * m_depth + depth;
	return m_pixelDataRGB[index];
}

void Image::setPixelValRGB(int row, int col, int depth, uint8_t val)
{
	int index = ((row * m_cols) + col) * m_depth + depth;
	m_pixelDataRGB[index]= val;
}
