#include "pca.h"
#include <iostream>
#include <io.h>

#include <time.h>

using namespace std;

//void getFiles(string path, string exd, vector<string>& files) {
//	//文件句柄
//	long   hFile = 0;
//	//文件信息
//	struct _finddata_t fileinfo;
//	string pathName, exdName;
//
//	//两个字符串相等，strcmp函数返回0
//	if (0 != strcmp(exd.c_str(), ""))
//	{
//		exdName = "\\*." + exd;
//	}
//	else
//	{
//		exdName = "\\*";
//	}
//
//	//_findfirst如果失败，则返回-1
//	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
//	{
//		do
//		{
//			//如果是文件夹中仍有文件夹,迭代之
//			//如果不是,加入列表
//			if ((fileinfo.attrib &  _A_SUBDIR))
//			{
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//					getFiles(pathName.assign(path).append("\\").append(fileinfo.name), exd, files);
//			}
//			else
//			{
//				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
//					files.push_back(pathName.assign(path).append("\\").append(fileinfo.name));
//			}
//		} while (_findnext(hFile, &fileinfo) == 0);
//
//		_findclose(hFile);
//	}
//
//	else
//		cout << -1 << endl;
//}

//vector<vector<int>> getTrainData(vector<string> files) {
//	vector<vector<int>> r;
//
//	int size = files.size();
//	for (int i = 0; i < size; i++) {
//		string path = files[i];
//		bitmap *image = new bitmap(path);
//		vector<int> imageData = image->getData();
//		image->closeFile();
//		r.push_back(imageData);
//	}
//
//	return r;
//}

int main() {
	clock_t start, finish;

	//get training set
	string filePath = "./images/ATT";
	/*vector<string> files;
	getFiles(filePath, "BMP", files);
	vector<vector<int>> trainData = getTrainData(files);*/

	//get test set
	/*bitmap *test = new bitmap("./test/2.bmp");*/
	Mat test = imread("./test/7.bmp", 0);
	//bitmap *test = new bitmap("C:/Users/Administrator/Desktop/ATT/s1/1.bmp");
	/*vector<int> testData = test->getData();
	test->closeFile();*/

	pca *pcaModel = new pca(filePath);
	/*test = test.reshape(0, 1);*/
	pcaModel->setTestData(test);
	//model->train(images, labels);

	start = clock();

	pcaModel->train();
	//int predictedLabel = model->predict(testSample);
	pcaModel->predict();

	//cout << "分类为： " << pcaModel->getPredictedLabel() << endl;
	cout << "路径为‘./test/7.bmp’的图片被预测的分类为 " << pcaModel->getPredictedLabel() << endl;

	finish = clock();

	cout << "训练和预测总用时: " << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	system("pause");

	return 0;
}