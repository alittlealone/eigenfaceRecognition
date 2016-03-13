#include "pca.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>


//转置
vector<vector<double>> transpose(vector<double> a) {
	vector<vector<double>> r;
	vector<double> rr;
	for (int i = 0; i < a.size(); i++) {
		rr.clear();
		rr.push_back(a[i]);
		r.push_back(rr);
	}
	return r;
}

vector<vector<int>> transpose(vector<int> a) {
	vector<vector<int>> r;
	vector<int> rr;
	for (int i = 0; i < a.size(); i++) {
		rr.clear();
		rr.push_back(a[i]);
		r.push_back(rr);
	}
	return r;
}

vector<vector<double>> transpose(vector<vector<double>> a) {
	vector<vector<double>> r;
	vector<double> rr;
	for (int i = 0; i < a[0].size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(a[j][i]);
		}
		r.push_back(rr);
	}
	return r;
}

vector<vector<int>> transpose(vector<vector<int>> a) {
	vector<vector<int>> r;
	vector<int> rr;
	for (int i = 0; i < a[0].size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(a[j][i]);
		}
		r.push_back(rr);
	}
	return r;
}

vector<double> operator+(vector<double> w, vector<double> x) {
	vector<double> r;
	for (int i = 0; i < w.size(); i++)
		r.push_back(w[i] + x[i]);
	return r;
}

vector<double> operator-(vector<int> w, vector<double> x) {
	vector<double> r;
	for (int i = 0; i < w.size(); i++)
		r.push_back(w[i] - x[i]);
	return r;
}


vector<double> operator/(vector<double> x, int y) {
	vector<double> r;
	for (int i = 0; i < x.size(); i++)
		r.push_back(x[i] / y);
	return r;
}

double operator*(vector<double> w, vector<double> x) {
	double r = 0;
	for (int i = 0; i < w.size(); i++)
		r += w[i] * x[i];
	return r;
}

double operator*(vector<double> w, vector<int> x) {
	double r = 0;
	for (unsigned int i = 0; i < w.size(); i++)
		r += w[i] * x[i];
	return r;
}

vector<double> operator*(vector<double> w, vector<vector<double>> x) {
	vector<double> r;
	vector<vector<double>> z = transpose(x);
	for (int i = 0; i < z.size(); i++)
		r.push_back(w * z[i]);
	return r;
}

vector<vector<double>> operator*(vector<vector<double>> x, vector<vector<double>> y) {
	vector<vector<double>> r;
	vector<vector<double>> z = transpose(y);
	vector<double> rr;
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < z.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(x[i] * z[j]);
		}
		r.push_back(rr);
	}
	return r;
}

vector<vector<double>> operator*(vector<vector<double>> x, vector<vector<int>> y) {
	vector<vector<double>> r;
	vector<vector<int>> z = transpose(y);
	vector<double> rr;
	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < z.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(x[i] * z[j]);
		}
		r.push_back(rr);
	}
	return r;
}

bool mySort(double a, double b) {
	return a > b;
}

//求向量2范数
double norm(vector<double> a) {
	double sum = 0;
	double r;
	for (int i = 0; i < a.size(); i++)
		sum += a[i] * a[i];
	r = sqrt(sum);
	return r;
}

//对每一维求均值
double average(vector<int> a) {
	double r = 0;
	int n = a.size();
	for (int i = 0; i < n; i++)
		r += a[i];
	return r / n;
}

double average(vector<double> a) {
	double r = 0;
	int n = a.size();
	for (int i = 0; i < n; i++)
		r += a[i];
	return r / n;
}

//一维矩阵间的协方差
double covariance(vector<double> x, vector<double> y) {
	double averageX = average(x);
	double averageY = average(y);
	double sum = 0;
	int n = x.size();
	for (int i = 0; i < n; i++)
		sum += (x[i] - averageX) * (y[i] - averageY);
	return sum / (n - 1);
}

void pca::setAverageFace() {
	vector<vector<int>> r = transpose(data);
	vector<double> means;
	for (int i = 0; i < r.size(); i++)
		means.push_back(average(r[i]));
	this->averageFace = means;
}

//零均值化
void pca::setZeroMeanVec() {
	vector<vector<double>> rr;
	vector<vector<int>> r = transpose(data);
	vector<double> rrr;
	for (int i = 0; i < r.size(); i++) {
		for (int j = 0; j < r[0].size(); j++) {
			if (j == 0)
				rrr.clear();
			rrr.push_back(r[i][j] - averageFace[i]);
		}
		rr.push_back(rrr);
	}
	this->zeroMeanVec = transpose(rr);
}

//!!!!!!
//直接求N^2 * N^2矩阵的特征值和特征向量，效率太低且占用内存太大
//对零均值化矩阵求协方差矩阵
/**
vector<vector<double>> pca::cov(vector<vector<double>> data) {
	vector<vector<double>> r;
	vector<vector<double>> dataTrans = transpose(data); //N2 * M
	vector<double> rr;
	for (int i = 0; i < dataTrans.size(); i++) {
		for (int j = 0; j < dataTrans.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(covariance(dataTrans[i], dataTrans[j]));
		}
		r.push_back(rr);
	}
	return r;  //N2 * N2
}
**/

///**
//令A为原矩阵零均值化后的矩阵(M * N^2)
//即要求A * A^T (N^2 * n^2)的特征向量
//经推导，其等价于求A^T * (A * A^T 的特征向量)
//所以先求A * A^T，等价于求cov(A, A^T)，等价于cov(data, data^T)
vector<vector<double>> pca::cov(vector<vector<double>> data) {
	vector<vector<double>> r;
	//data -- M * N2
	vector<double> rr;
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(covariance(data[i], data[j]));
		}
		r.push_back(rr);
	}
	return r;  //M * M
}
//**/

//用雅可比算法求协方差矩阵特征值和特征向量
bool pca::eigen(vector<vector<double>> c, vector<vector<double>>& eigenVector, vector<double>& eigenValue) {
	int n = c.size();
	double m;
	int p, q;

	vector<double> a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == 0)
				a.clear();
			if (i == j)
				a.push_back(1);
			else
				a.push_back(0);
		}
		eigenVector.push_back(a);
	}

	int cycles = 0;
	double x, y, omega;
	double sin2theta, sintheta, costheta, cos2theta;
	while (1) {
		m = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if ((i != j) && (abs(c[i][j]) > m)) {
					m = abs(c[i][j]);
					p = i;
					q = j;
				}
			}
		}

		if (m <= EPS)
			break;
		if (cycles > MAXCYCLES)
			return false;

		cycles++;

		x = (-1) * c[p][q];
		y = (c[q][q] - c[p][p]) / 2;
		if (y >= 0)
			omega = x / sqrt(pow(x, 2) + pow(y, 2));
		else
			omega = (-1) * x / sqrt(pow(x, 2) + pow(y, 2));
		sin2theta = omega;
		cos2theta = sqrt(1 - pow(sin2theta, 2));
		sintheta = omega / sqrt(2 * (1 + sqrt(1 - pow(omega, 2))));
		costheta = sqrt(1 - pow(sintheta, 2));

		double cpp = c[p][p];
		double cqq = c[q][q];
		double cpq = c[p][q];
		c[p][p] = cpp * pow(costheta, 2) + cqq * pow(sintheta, 2) + cpq * sin2theta;
		c[q][q] = cpp * pow(sintheta, 2) + cqq * pow(costheta, 2) - cpq * sin2theta;
		c[p][q] = 0.5 * (cqq - cpp) * sin2theta + cpq * cos2theta;
		c[q][p] = c[p][q];

		for (int j = 0; j < n; j++) {
			if ((j != p) && (j != q)) {
				double cpj = c[p][j];
				c[p][j] = cpj * costheta + c[q][j] * sintheta;
				c[q][j] = (-1) * cpj * sintheta + c[q][j] * costheta;
			}
		}
		for (int i = 0; i < n; i++) {
			if ((i != p) && (i != q)) {
				double cip = c[i][p];
				c[i][p] = cip * costheta + c[i][q] * sintheta;
				c[i][q] = (-1) * cip * sintheta + c[i][q] * costheta;
			}
		}

		for (int i = 0; i < n; i++) {
			double vip = eigenVector[i][p];
			eigenVector[i][p] = vip * costheta + eigenVector[i][q] * sintheta;
			eigenVector[i][q] = (-1) * vip * sintheta + eigenVector[i][q] * costheta;
		}
	}

	map<double, int> eigenMap;
	for (int i = 0; i < n; i++) {
		eigenValue.push_back(c[i][i]);
		eigenMap[eigenValue[i]] = i;
	}

	eigenVector = transpose(zeroMeanVec) * eigenVector;

	sort(eigenValue.begin(), eigenValue.end(), mySort);
	vector<vector<double>> temp = transpose(eigenVector);
	vector<vector<double>> eigenVectorSorted;
	for (int i = 0; i < n; i++) {
		eigenVectorSorted.push_back(temp[eigenMap[eigenValue[i]]]);
	}
	
	for (int i = 0; i < eigenVectorSorted.size(); i++) {
		double k = norm(eigenVectorSorted[i]);
		for (int j = 0; j < eigenVectorSorted[i].size(); j++)
			eigenVectorSorted[i][j] /= k;
	}

	eigenVector = transpose(eigenVectorSorted);

	for (int j = 0; j < n; j++) {
		double sumVec = 0;
		for (int i = 0; i < n; i++)
			sumVec += eigenVector[i][j];
		if (sumVec < 0) {
			for (int i = 0; i < n; i++)
				eigenVector[i][j] *= -1;
		}
	}

	return true;
}

//保留前n个特征值对应的特征向量，组成新的特征空间向量基
//每列为一个特征向量
vector<vector<double>> eigenSpace(vector<vector<double>> eigenVector, int n) {
	vector<vector<double>> r;
	vector<vector<double>> data = transpose(eigenVector);
	for (int i = 0; i < n; i++)
		r.push_back(data[i]);
	return transpose(r);
}

//选择保留的主成分个数
int pca::chooseN(vector<double> eigenValue) {
	double sum = 0;
	for (int i = 0; i < eigenValue.size(); i++)
		sum += eigenValue[i];
	int k;
	double sumK = 0;
	for (k = 0; k < eigenValue.size(); k++) {
		sumK += eigenValue[k];
		if (sumK >= THRESHOLD * sum)
			break;
	}

	cout << "选择主成分的阈值为： " << THRESHOLD << endl;
	cout << "N = " << k + 1 << endl;

	for (int i = 0; i < 10; i++)
		cout << "第" << i << "特征值为: " << eigenValue[i] << endl;

	return k + 1;
}

//计算Euclidian distance
double euclidianDistance(vector<double> a, vector<double> b) {
	double r = 0;
	for (int i = 0; i < a.size(); i++)
		r += (a[i] - b[i]) * (a[i] - b[i]);
	return r;
}

pca::pca(vector<vector<int>> data) {
	this->data = data;
}

pca::~pca(){}

//string pca::getTestFile() {
//	return file;
//}

//void pca::setTestFile(string file) {
//	this->file = file;
//}

vector<vector<int>> pca::getData() {
	return data;
}

void pca::setData(vector<vector<int>> data) {
	this->data = data;
}

void pca::setTestData(vector<int> data) {
	this->testData = data;
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

//vector<vector<double>> pca::readData(string fileName) {
//	ifstream in;
//	vector<vector<double>> data;
//	string s;
//	double val;
//	in.open(fileName.c_str());
//	if (!in)
//		cout << "打开文件失败！" << endl;
//	else {
//		while (getline(in, s)) {
//			istringstream iss(s);
//			vector<double> data0;
//			while (iss >> val)
//				data0.push_back(val);
//			data.push_back(data0);
//			data0.clear();
//		}
//	}
//	in.close();
//	return data;
//}

void pca::train() {
	setAverageFace();
	setZeroMeanVec();
	//vector<vector<double>> covVec = cov(zeroMeanVec);
	vector<vector<double>> covVec = zeroMeanVec * transpose(zeroMeanVec);
	vector<vector<double>> eigenVector;
	vector<double> eigenValue;
	bool ifGetEigen = eigen(covVec, eigenVector, eigenValue);
	if (!ifGetEigen)
		cout << "未能求出特征值和特征向量！";
	else {
		this->selectedEigen = eigenSpace(eigenVector, chooseN(eigenValue));
		cout << "Maybe succeed!" << endl;
	}
	
	/*cout << "selectedEigen.size() = " << selectedEigen.size() << endl;
	cout << "selectedEigen[0].size() = " << selectedEigen[0].size() << endl;
	cout << endl;*/

	this->projectedFace = zeroMeanVec * selectedEigen;

	/*cout << "projectedFace.size() = " << projectedFace.size() << endl;
	cout << "projectedFace[0].size() = " << projectedFace[0].size() << endl;*/

	setLabel("./images/ATT");
	map<int, vector<double>> averageProjectedFace;

	map<int, vector<double>> personToTotalFace; //人--脸向量总和
	map<int, int> personToCount;//人--该人的脸图片总张数
	map<int, vector<double>>::iterator itTotal;
	for (int i = 0; i < data.size(); i++) {
		int j = label[i];

		itTotal = personToTotalFace.find(j);
		//没找到
		if (itTotal == personToTotalFace.end()) {
			personToTotalFace[j] = projectedFace[i];
			personToCount[j] = 1;
		}
		//找到了
		else {
			personToTotalFace[j] = personToTotalFace[j] + projectedFace[i];
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
	vector<double> projectedTestFace = (testData - averageFace) * selectedEigen;
	//求testData和每个training中的降过维的face之间的欧拉距离
	map<int, double> distanceMap;
	map<int, vector<double>>::iterator it;
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
