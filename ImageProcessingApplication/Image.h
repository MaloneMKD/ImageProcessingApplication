#pragma once

#include <vector>

class Image
{
public:
	// Contructors and Destructor
	Image();
	Image(int numRows, int numCols, int depth);

	// Getters and Setters
	uint8_t getPixelVal(int row, int col);
	void setPixelVal(int row, int col, uint8_t val);

	uint8_t getPixelValRGB(int row, int col, int depth);
	void setPixelValRGB(int row, int col, int depth, uint8_t val);

	// Member variables
	int m_rows;
	int m_cols;
	int m_depth;
	std::vector<uint8_t> m_pixelData;
	std::vector<uint8_t> m_pixelDataRGB;
};

