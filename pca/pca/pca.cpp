#include "pca.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

bool mySort(double a, double b) {
	return a > b;
}

//对每一维求均值
double average(vector<double> a) {
	double r = 0;
	int n = a.size();
	for (int i = 0; i < n; i++)
		r += a[i];
	return r / n;
}

//转置
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

//零均值化
vector<vector<double>> pca::zeroMean(vector<vector<double>> data) {
	vector<vector<double>> r = transpose(data);
	vector<double> means;
	for (int i = 0; i < r.size(); i++)
		means.push_back(average(r[i]));
	for (int i = 0; i < r.size(); i++) {
		for (int j = 0; j < r[0].size(); j++)
			r[i][j] -= means[i];
	}
	return transpose(r);
}

//对零均值化矩阵求协方差矩阵
vector<vector<double>> pca::cov(vector<vector<double>> data) {
	vector<vector<double>> r;
	vector<vector<double>> dataTrans = transpose(data);
	vector<double> rr;
	for (int i = 0; i < dataTrans.size(); i++) {
		for (int j = 0; j < dataTrans.size(); j++) {
			if (j == 0)
				rr.clear();
			rr.push_back(covariance(dataTrans[i], dataTrans[j]));
		}
		r.push_back(rr);
	}
	return r;
}

//用雅可比算法求协方差矩阵特征值和特征向量
bool eigen(vector<vector<double>> c, vector<vector<double>>& eigenVector, vector<double>& eigenValue) {
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

	sort(eigenValue.begin(), eigenValue.end(), mySort);
	vector<vector<double>> temp = transpose(eigenVector);
	vector<vector<double>> eigenVectorSorted;
	for (int i = 0; i < n; i++) {
		eigenVectorSorted.push_back(temp[eigenMap[eigenValue[i]]]);
	}
	eigenVectorSorted = transpose(eigenVectorSorted);

	eigenVector = eigenVectorSorted;

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
	return k + 1;
}

pca::pca(string file) {
	this->file = file;
	this->data = readData(file);
}

pca::~pca(){}

string pca::getTestFile() {
	return file;
}

void pca::setTestFile(string file) {
	this->file = file;
}

vector<vector<double>> pca::getData() {
	return data;
}

void pca::setData(vector<vector<double>> data) {
	this->data = data;
}

vector<vector<double>> pca::readData(string fileName) {
	ifstream in;
	vector<vector<double>> data;
	string s;
	double val;
	in.open(fileName.c_str());
	if (!in)
		cout << "打开文件失败！" << endl;
	else {
		while (getline(in, s)) {
			istringstream iss(s);
			vector<double> data0;
			while (iss >> val)
				data0.push_back(val);
			data.push_back(data0);
			data0.clear();
		}
	}
	in.close();
	return data;
}

void pca::getEigen(vector<vector<double>> data) {
	vector<vector<double>> zeroMeanVec = zeroMean(data);
	vector<vector<double>> covVec = cov(zeroMeanVec);
	vector<vector<double>> eigenVector;
	vector<double> eigenValue;
	bool ifGetEigen = eigen(covVec, eigenVector, eigenValue);
	if (!ifGetEigen)
		cout << "未能求出特征值和特征向量！";
	else {
		int n = eigenValue.size();
		vector<vector<double>> selectedEigen = eigenSpace(eigenVector, chooseN(eigenValue));
		for (int i = 0; i < selectedEigen.size(); i++) {
			for (int j = 0; j < selectedEigen[0].size(); j++) {
				cout << selectedEigen[i][j] << " ";
			}
			cout << endl;
		}
	}
	system("pause");
}