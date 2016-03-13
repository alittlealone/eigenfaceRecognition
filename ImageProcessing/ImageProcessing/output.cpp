#include "bitmap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<char> fileBuffer;
PBITMAPFILEHEADER fileHeader;
PBITMAPINFOHEADER infoHeader;

std::ifstream file("inputData.txt");
std::ofstream outputfile("output.bmp", std::ios::binary);

vector<vector<int>> readData(ifstream file) {
	vector<vector<int> > data;
	string s;
	int val;
	if (!file)
		cout << "打开文件失败！" << endl;
	else {
		while (getline(file, s)) {
			istringstream iss(s);
			vector<int> data0;
			while (iss >> val)
				data0.push_back(val);
			data.push_back(data0);
			data0.clear();
		}
	}
	file.close();
	return data;
}

int main() {
	vector<vector<int>> data = readData(file);

	fileHeader->bfType = 0x4D42;             //'BM'
	fileHeader->bfSize;
	fileHeader->bfReserved1 = 0;
	fileHeader->bfReserved2 = 0;
	fileHeader->bfOffBits;

	infoHeader->biSize = sizeof(*PBITMAPINFOHEADER);
	infoHeader->biWidth = data[0].size();
	infoHeader->biHeight = data.size();
	infoHeader->biBitCount;
	infoHeader->biCompression;
	infoHeader->biSizeImage;
	infoHeader->biXPelsPerMeter;
	infoHeader->biYPelsPerMeter;
	infoHeader->biClrUsed;
	infoHeader->biClrImportant;


}