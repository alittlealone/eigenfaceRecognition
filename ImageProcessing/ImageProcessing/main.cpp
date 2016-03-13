#include <iostream>
#include <fstream>
#include <vector>
#include "bitmap.h"  // contains information of elements in bitmap image header

using namespace std;

vector<char> fileBuffer;
PBITMAPFILEHEADER fileHeader;
PBITMAPINFOHEADER infoHeader;

//std::ifstream file("test_8bit.bmp", std::ios::binary);
//std::ofstream outputfile("output.bmp", std::ios::binary);
//ifstream file;
//file.open("data.bmp", ios::in | ios::binary);
std::ifstream file("data.bmp", std::ios::binary);
std::ofstream outputfile("intputTest.bmp", std::ios::binary);

vector<vector<int>> data;

void openFile() {

	if (file) {
		//set file cursor to beginning of file, read till end of file to determine length, set cursor back to beginning
		file.seekg(0, std::ios::end);
		streampos fileLength = file.tellg();
		file.seekg(0, std::ios::beg);

		//read contents of file into buffer
		fileBuffer.resize(fileLength);
		file.read(&fileBuffer[0], fileLength);

		//read file contents into file header and info header
		fileHeader = (PBITMAPFILEHEADER)(&fileBuffer[0]);
		infoHeader = (PBITMAPINFOHEADER)(&fileBuffer[0] + sizeof(BITMAPFILEHEADER));

		//set file cursor to beginning of pixel data
		file.seekg(fileHeader->bfOffBits, std::ios::beg);

		int imageArea = infoHeader->biWidth * infoHeader->biHeight;
		int pixel = 0;
		int pixelValue;


		//Print pixel values to screen to test validity
		/**
		for (int position = fileHeader->bfOffBits; position < (fileHeader->bfOffBits + infoHeader->biWidth); position++) {

		cout << "Pixel: " << pixel << " Value: "
		<< position << " = " << (int)fileBuffer[position] << endl;
		pixel++;
		}
		**/


		//test to write unaltered input file to output file for sanity check
		for (int i = 0; i < fileLength; i++) {
		outputfile << fileBuffer[i];
		}
		outputfile.close();
		//end output test

		vector<int> a;
		int row = infoHeader->biHeight;
		int col = infoHeader->biWidth;

		int pos = fileHeader->bfOffBits;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					a.clear();
				int b = (int)fileBuffer[pos++];
				if (b < 0)
					a.push_back(256 + b);
				else
					a.push_back(b);
			}
			data.push_back(a);
		}

		for (int i = data.size() - 1; i >= 0; i--) {
			for (int j = 0; j < data[0].size(); j++) {
				cout << data[i][j] << " ";
			}
			cout << endl;
		}



	}
	else {
		cout << "File does not exist!" << endl;
		exit;
	}


}

void closeFile() {

	file.close();

}



//Used to print relevant file parameters to user for a sanity check
void fileStats() {

	cout << "\n\nFile Parameters:\n";
	cout << fileBuffer[0] << " " << fileBuffer[1] << endl;
	cout << "Offset in bytes to pixels: " << fileHeader->bfOffBits << endl;
	cout << "Size of file in bytes: " << fileHeader->bfSize << endl;
	cout << "Number of pixels wide: " << infoHeader->biWidth << endl;
	cout << "Number of pixels tall: " << infoHeader->biHeight << endl;
	cout << "Bits per pixel: " << infoHeader->biBitCount << endl;
	cout << "The compression type is: " << infoHeader->biCompression << endl;


	cout << "\n\nPress any key to exit";
	cin.get();

}

int main()
{
	//TO DO: add command line arguments to parse actions to be performed on file
	// -h   -> Prints program usage and list of switches
	//OR: dump out an image for each operation with a _operation name appended

	//file.open("data.bmp", ios::in | ios::binary);

	openFile();

	fileStats();

	closeFile();



	return 0;
}