#ifndef BITMAP_H
#define BITMAP_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;


typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#pragma pack(2)

typedef struct tagBITMAPFILEHEADER {
	WORD  bfType;       // The file type; must be BM
	DWORD bfSize;       // The size, in bytes, of the bitmap file.
	WORD  bfReserved1;  // Reserved; must be zero.
	WORD  bfReserved2;  // Reserved; must be zero.
	DWORD bfOffBits;    // The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits.
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;           // The number of bytes required by the structure.
	LONG  biWidth;          // The width of the bitmap, in pixels.
	LONG  biHeight;         // The height of the bitmap, in pixel.  
	WORD  biPlanes;         // The number of planes for the target device. This value must be set to 1.
	WORD  biBitCount;       // The number of bits-per-pixel. 
	DWORD biCompression;    // The type of compression.  
	DWORD biSizeImage;      // The size, in bytes, of the image.
	LONG  biXPelsPerMeter;  // The horizontal resolution, in pixels-per-meter.
	LONG  biYPelsPerMeter;  // The vertical resolution, in pixels-per-meter.
	DWORD biClrUsed;        // The number of color indexes in the color table that are actually used by the bitmap.
	DWORD biClrImportant;   // The number of color indexes that are required for displaying the bitmap.
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;


class bitmap {
private:
	string fileName;
	ifstream file;
	PBITMAPFILEHEADER fileHeader;
	PBITMAPINFOHEADER infoHeader;
	vector<char> fileBuffer;
	vector<int> data;

public:
	bitmap(std::string fileName);
	vector<int> getData();
	void closeFile();
};

#endif