#include "cv.h"
#include "highgui.h"
#include <fstream>
#include <string>
#include <vector>
#include <io.h>

using namespace std;
using namespace cv;

//Mat normalize(const Mat& src) {
//	Mat srcnorm;
//	normalize(src, srcnorm, 0, 255, NORM_MINMAX, CV_8UC1);
//	return srcnorm;
//}

void getFiles(string path, string exd, vector<string>& files) {
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string pathName, exdName;

	//两个字符串相等，strcmp函数返回0
	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}
	else
	{
		exdName = "\\*";
	}

	//_findfirst如果失败，则返回-1
	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是文件夹中仍有文件夹,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
			}
			else
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);
	}

	else
		cout << -1 << endl;
}

int main(int argc, char *argv[]) {
	vector<string> files;
	string filePath = "./images/ATT";
	getFiles(filePath, "BMP", files);

	vector<Mat> originalData;
	int size = files.size();
	for (int i = 0; i < size; i++) {
		string path = files[i];
		Mat image = imread(path, 0);
		originalData.push_back(image);
	}


	//// load greyscale images (these are from http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html)
	//db.push_back(imread("s1/1.bmp", 0));
	//db.push_back(imread("s1/2.bmp", 0));
	//db.push_back(imread("s1/3.bmp", 0));

	//db.push_back(imread("s2/1.bmp", 0));
	//db.push_back(imread("s2/2.bmp", 0));
	//db.push_back(imread("s2/3.bmp", 0));

	//int total = db[0].rows * db[0].cols;
	int number = originalData.size();
	int pixels = originalData[0].rows * originalData[0].cols;

	// build matrix (row)
	Mat mat(number, pixels, CV_32FC1);
	for (int i = 0; i < number; i++) {
		Mat X = mat.row(i);
		originalData[i].reshape(1, 1).row(0).convertTo(X, CV_32FC1, 1/255.);
	}

	ofstream fout("./mat.txt");
	fout << " " << mat.row(0) << endl;

	// Change to the number of principal components you want:
	//int numPrincipalComponents = 12;

	//// Do the PCA:
	//PCA pca(mat, Mat(), CV_PCA_DATA_AS_COL, numPrincipalComponents);

	//// Create the Windows:
	//namedWindow("avg", 1);
	//namedWindow("pc1", 1);
	//namedWindow("pc2", 1);
	//namedWindow("pc3", 1);

	//// Mean face:
	//imshow("avg", pca.mean.reshape(1, db[0].rows));

	//// First three eigenfaces:
	//imshow("pc1", normalize(pca.eigenvectors.row(0)).reshape(1, db[0].rows));
	//imshow("pc2", normalize(pca.eigenvectors.row(1)).reshape(1, db[0].rows));
	//imshow("pc3", normalize(pca.eigenvectors.row(2)).reshape(1, db[0].rows));

	// Show the windows:
	waitKey(0);
}