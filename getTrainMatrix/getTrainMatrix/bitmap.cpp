#include <iostream>
#include <fstream>
#include "bitmap.h"

bitmap::bitmap(string fileName) {
	this->fileName = fileName;
	this->file.open(fileName, ios::in | ios::binary);
	if (file) {
		//set file cursor to beginning of file, read till end of file to determine length, set cursor back to beginning
		file.seekg(0, std::ios::end);
		streampos fileLength = file.tellg();
		file.seekg(0, std::ios::beg);

		//read contents of file into buffer
		fileBuffer.resize(fileLength);
		file.read(&fileBuffer[0], fileLength);

		//read file contents into file header and info header
		this->fileHeader = (PBITMAPFILEHEADER)(&fileBuffer[0]);
		this->infoHeader = (PBITMAPINFOHEADER)(&fileBuffer[0] + sizeof(BITMAPFILEHEADER));
	}
	else {
		cout << "File does not exist!" << endl;
		exit;
	}
}

vector<int> bitmap::getData() {
	file.seekg(0, std::ios::end);
	streampos fileLength = file.tellg();
	file.seekg(fileHeader->bfOffBits, std::ios::beg);

	for (int i = fileHeader->bfOffBits; i < fileLength; i++) {
		int b = (int)fileBuffer[i];
		if (b < 0)
			data.push_back(256 + b);
		else
			data.push_back(b);
	}

	return data;
}

void bitmap::closeFile() {
	file.close();
}