#include "pca.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <io.h>


bool mySort(double a, double b) {
	return a > b;
}

void pca::setAverageFace() {
	Mat data_tmp;
	data.copyTo(data_tmp);
	Mat sum = data_tmp.row(0);

	for(int i = 1; i < number; i++) {
		sum += data_tmp.row(i);
	}
	this->averageFace = sum / number;
}

void pca::setZeroMeanVec() {
	Mat r(number, pixels, CV_32FC1);
	for(int i = 0; i < number; i++) {
		Mat r_row = r.row(i);
		Mat diff = data.row(i) - averageFace;
		diff.copyTo(r_row);
	}
	this->zeroMeanVec = r;
}


//令A为原矩阵零均值化后的矩阵(M * N^2)
//即要求A * A^T (N^2 * n^2)的特征向量
//经推导，其等价于求A^T * (A * A^T 的特征向量)
//所以先求A * A^T，等价于求cov(A, A^T)，等价于cov(data, data^T)
//vector<vector<double>> pca::cov(vector<vector<double>> data) {
//	vector<vector<double>> r;
//	//data -- M * N2
//	vector<double> rr;
//	for (int i = 0; i < data.size(); i++) {
//		for (int j = 0; j < data.size(); j++) {
//			if (j == 0)
//				rr.clear();
//			rr.push_back(covariance(data[i], data[j]));
//		}
//		r.push_back(rr);
//	}
//	return r;  //M * M
//}
//

//用雅可比算法求协方差矩阵特征值和特征向量
//bool pca::eigen(vector<vector<double>> c, vector<vector<double>>& eigenVector, vector<double>& eigenValue) {
//	int n = c.size();
//	double m;
//	int p, q;
//
//	vector<double> a;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			if (j == 0)
//				a.clear();
//			if (i == j)
//				a.push_back(1);
//			else
//				a.push_back(0);
//		}
//		eigenVector.push_back(a);
//	}
//
//	int cycles = 0;
//	double x, y, omega;
//	double sin2theta, sintheta, costheta, cos2theta;
//	while (1) {
//		m = 0;
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < i; j++) {
//				if ((i != j) && (abs(c[i][j]) > m)) {
//					m = abs(c[i][j]);
//					p = i;
//					q = j;
//				}
//			}
//		}
//
//		if (m <= EPS)
//			break;
//		if (cycles > MAXCYCLES)
//			return false;
//
//		cycles++;
//
//		x = (-1) * c[p][q];
//		y = (c[q][q] - c[p][p]) / 2;
//		if (y >= 0)
//			omega = x / sqrt(pow(x, 2) + pow(y, 2));
//		else
//			omega = (-1) * x / sqrt(pow(x, 2) + pow(y, 2));
//		sin2theta = omega;
//		cos2theta = sqrt(1 - pow(sin2theta, 2));
//		sintheta = omega / sqrt(2 * (1 + sqrt(1 - pow(omega, 2))));
//		costheta = sqrt(1 - pow(sintheta, 2));
//
//		double cpp = c[p][p];
//		double cqq = c[q][q];
//		double cpq = c[p][q];
//		c[p][p] = cpp * pow(costheta, 2) + cqq * pow(sintheta, 2) + cpq * sin2theta;
//		c[q][q] = cpp * pow(sintheta, 2) + cqq * pow(costheta, 2) - cpq * sin2theta;
//		c[p][q] = 0.5 * (cqq - cpp) * sin2theta + cpq * cos2theta;
//		c[q][p] = c[p][q];
//
//		for (int j = 0; j < n; j++) {
//			if ((j != p) && (j != q)) {
//				double cpj = c[p][j];
//				c[p][j] = cpj * costheta + c[q][j] * sintheta;
//				c[q][j] = (-1) * cpj * sintheta + c[q][j] * costheta;
//			}
//		}
//		for (int i = 0; i < n; i++) {
//			if ((i != p) && (i != q)) {
//				double cip = c[i][p];
//				c[i][p] = cip * costheta + c[i][q] * sintheta;
//				c[i][q] = (-1) * cip * sintheta + c[i][q] * costheta;
//			}
//		}
//
//		for (int i = 0; i < n; i++) {
//			double vip = eigenVector[i][p];
//			eigenVector[i][p] = vip * costheta + eigenVector[i][q] * sintheta;
//			eigenVector[i][q] = (-1) * vip * sintheta + eigenVector[i][q] * costheta;
//		}
//	}
//
//	map<double, int> eigenMap;
//	for (int i = 0; i < n; i++) {
//		eigenValue.push_back(c[i][i]);
//		eigenMap[eigenValue[i]] = i;
//	}
//
//	eigenVector = transpose(zeroMeanVec) * eigenVector;
//
//	sort(eigenValue.begin(), eigenValue.end(), mySort);
//	vector<vector<double>> temp = transpose(eigenVector);
//	vector<vector<double>> eigenVectorSorted;
//	for (int i = 0; i < n; i++) {
//		eigenVectorSorted.push_back(temp[eigenMap[eigenValue[i]]]);
//	}
//
//	for (int i = 0; i < eigenVectorSorted.size(); i++) {
//		double k = norm(eigenVectorSorted[i]);
//		for (int j = 0; j < eigenVectorSorted[i].size(); j++)
//			eigenVectorSorted[i][j] /= k;
//	}
//
//	eigenVector = transpose(eigenVectorSorted);
//
//	for (int j = 0; j < n; j++) {
//		double sumVec = 0;
//		for (int i = 0; i < n; i++)
//			sumVec += eigenVector[i][j];
//		if (sumVec < 0) {
//			for (int i = 0; i < n; i++)
//				eigenVector[i][j] *= -1;
//		}
//	}
//
//	return true;
//}

//保留前n个特征值对应的特征向量，组成新的特征空间向量基
//每行为一个特征向量
Mat eigenSpace(Mat eigenVector, int n) {
	Mat r(n, eigenVector.cols, CV_32FC1);
	/*Mat data = eigenVector.t();*/
	for (int i = 0; i < n; i++) {
		Mat r_row = r.row(i);
		eigenVector.row(i).copyTo(r_row);
	}

	ofstream f("./eigenSpaceValue.txt");
	f << r << endl;

	return r;
}

//选择保留的主成分个数
//int pca::chooseN(vector<double> eigenValue) {
//	double sum = 0;
//	for (int i = 0; i < eigenValue.size(); i++)
//		sum += eigenValue[i];
//	int k;
//	double sumK = 0;
//	for (k = 0; k < eigenValue.size(); k++) {
//		sumK += eigenValue[k];
//		if (sumK >= THRESHOLD * sum)
//			break;
//	}
//
//	cout << "选择主成分的阈值为： " << THRESHOLD << endl;
//	cout << "N = " << k + 1 << endl;
//
//	for (int i = 0; i < 10; i++)
//		cout << "第" << i << "特征值为: " << eigenValue[i] << endl;
//
//	return k + 1;
//}

int pca::chooseN(Mat eigenValue) {
	float sum = 0;
	for (int i = 0; i < eigenValue.rows; i++) {
		sum += eigenValue.at<float>(i, 0);
	}
	int k;
	float sumK = 0;
	for (k = 0; k < eigenValue.rows; k++) {
		sumK += eigenValue.at<float>(k, 0);
		if (sumK >= THRESHOLD * sum)
			break;
	}

	cout << "选择主成分的阈值为： " << THRESHOLD << endl;
	cout << "N = " << k + 1 << endl;

	return k + 1;
}

//计算Euclidian distance
//double euclidianDistance(vector<double> a, vector<double> b) {
//	double r = 0;
//	for (int i = 0; i < a.size(); i++)
//		r += (a[i] - b[i]) * (a[i] - b[i]);
//	return r;
//}

double euclidianDistance(Mat a, Mat b) {
	float r = 0;
	//可能不对，不知道数据结构！！！
	for (int i = 0; i < a.cols; i++) {
		r += (a.at<float>(0, i) - b.at<float>(0, i)) * (a.at<float>(0, i) - b.at<float>(0, i));
	}
	return r;
}


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

pca::pca(string filePath) {
	vector<string> files;
	getFiles(filePath, "BMP", files);

	vector<Mat> originalData;
	int size = files.size();
	for (int i = 0; i < size; i++) {
		string path = files[i];
		Mat image = imread(path, 0);
		originalData.push_back(image);
	}
	this->originalData = originalData;

	number = originalData.size();
	pixels = originalData[0].rows * originalData[0].cols;

	Mat data(number, pixels, CV_32FC1);
	for (int i = 0; i < number; i++) {
		Mat X = data.row(i);
		originalData[i].reshape(1, 1).row(0).convertTo(X, CV_32FC1, 1 / 255.);
	}

	/*ofstream fout("./data.txt");
	fout << " " << data << endl;*/

	this->data = data;
}

pca::~pca(){}

int pca::getPixels() {
	return pixels;
}

void pca::setTestData(Mat data) {
	this->testData = data;
}

vector<Mat> pca::getOriginalData() {
	return originalData;
}

void pca::setOriginalData(vector<Mat> originalData) {
	this->originalData = originalData;
}

Mat pca::getData() {
	return data;
}

void pca::setData(Mat data) {
	this->data = data;
}

void pca::setLabel(string path) {
	vector<int> label;
	if (path == "./images/ATT") {
		for (int i = 0; i < 63; i++)
			label.push_back(i / 9 + 1);
		this->label = label;
	}
	else
		cout << "没有该数据库所对应的label!" << endl;
}

int pca::getPredictedLabel() {
	return this->predictedLabel;
}

void pca::train() {
	setAverageFace();
	setZeroMeanVec();
	Mat covVec = zeroMeanVec * zeroMeanVec.t();
	Mat eigenVector;
	Mat eigenValue;
	/*vector<vector<double>> eigenVector;
	vector<double> eigenValue;*/
	bool ifGetEigen = eigen(covVec, true, eigenValue, eigenVector);
	//bool ifGetEigen = eigen(covVec, eigenVector, eigenValue);
	if (!ifGetEigen)
		cout << "未能求出特征值和特征向量！";
	else {
		/*ofstream fouout("./eigenValue.txt");
		fouout << eigenValue << endl;
		ofstream f("./eigenVector.txt");
		f << eigenVector << endl;*/
		//eigenvectors – output matrix of eigenvectors; it has the same size and type as src; the eigenvectors are 
		//stored as subsequent matrix rows, in the same order as the corresponding eigenvalues.
		//注意！改数据结构后每行为一个特征向量！全改为其转置！
		//列：eigenVector = zeroMeanVec.t() * eigenVector;
		eigenVector = (zeroMeanVec.t() * eigenVector.t()).t();//63*10304
		this->selectedEigen = eigenSpace(eigenVector, chooseN(eigenValue));//56*10304

		/*ofstream f("./selectedEigen.txt");
		f << selectedEigen << endl;*/

		cout << "Maybe succeed!" << endl;
	}

	/*cout << "selectedEigen.size() = " << selectedEigen.size() << endl;
	cout << "selectedEigen[0].size() = " << selectedEigen[0].size() << endl;
	cout << endl;*/
	//63 * 10304    10304 * 56
	this->projectedFace = zeroMeanVec * selectedEigen.t();
	/*ofstream fouout("./projectedFace.txt");
	fouout << projectedFace << endl;*/

	/*cout << "projectedFace.size() = " << projectedFace.size() << endl;
	cout << "projectedFace[0].size() = " << projectedFace[0].size() << endl;*/

	setLabel("./images/ATT");
	map<int, Mat> averageProjectedFace;
	map<int, Mat> personToTotalFace;//人--脸向量总和
	map<int, int> personToCount;//人--该人的脸图片总张数
	map<int, Mat>::iterator itTotal;
	for (int i = 0; i < data.rows; i++) {
		int j = label[i];

		itTotal = personToTotalFace.find(j);
		//没找到
		if (itTotal == personToTotalFace.end()) {
			personToTotalFace[j] = projectedFace.row(i);
			personToCount[j] = 1;
		}
		//找到了
		else {
			personToTotalFace[j] = personToTotalFace[j] + projectedFace.row(i);
			personToCount[j]++;
		}
	}
	for (itTotal = personToTotalFace.begin(); itTotal != personToTotalFace.end(); ++itTotal) {
		averageProjectedFace[itTotal->first] = itTotal->second / personToCount[itTotal->first];
	}

	this->averageProjectedFace = averageProjectedFace;
}

//先假设输入的图片一定是人脸
//并假设输入的人脸图片一定是训练集中其中一个人的脸
void pca::predict() {
	//把testData降维
	testData.convertTo(testData, CV_32FC1, 1 / 255.);

	Mat projectedTestFace = (testData - averageFace) * selectedEigen.t();//1*10304 * 10304*56
	ofstream f("./projectedTestFace.txt");
	f << projectedTestFace << endl;
	//求testData和每个training中的降过维的face之间的欧拉距离
	map<int, double> distanceMap;
	map<int, Mat>::iterator it;
	for (it = averageProjectedFace.begin(); it != averageProjectedFace.end(); ++it) {
		distanceMap[it->first] = euclidianDistance(it->second, projectedTestFace);
	}
	//距离最小的那个即为匹配的人
	map<int, double>::iterator itDistance = distanceMap.begin();
	int predictedLabel = itDistance->first;
	for (itDistance = distanceMap.begin(); itDistance != distanceMap.end(); ++itDistance) {
		cout << itDistance->first << " " << itDistance->second << endl;
	}
	for (itDistance = distanceMap.begin(); itDistance != distanceMap.end(); ++itDistance) {
		if (itDistance->second < distanceMap[predictedLabel])
			predictedLabel = itDistance->first;
	}
	this->predictedLabel = predictedLabel;
}
