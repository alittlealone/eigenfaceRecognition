#include "pca.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <math.h>


//ת��
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

//������2����
double norm(vector<double> a) {
	double sum = 0;
	double r;
	for (int i = 0; i < a.size(); i++)
		sum += a[i] * a[i];
	r = sqrt(sum);
	return r;
}

//��ÿһά���ֵ
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

//һά������Э����
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

//���ֵ��
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
//ֱ����N^2 * N^2���������ֵ������������Ч��̫����ռ���ڴ�̫��
//�����ֵ��������Э�������
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
//��AΪԭ�������ֵ����ľ���(M * N^2)
//��Ҫ��A * A^T (N^2 * n^2)����������
//���Ƶ�����ȼ�����A^T * (A * A^T ����������)
//��������A * A^T���ȼ�����cov(A, A^T)���ȼ���cov(data, data^T)
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

//���ſɱ��㷨��Э�����������ֵ����������
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

//����ǰn������ֵ��Ӧ����������������µ������ռ�������
//ÿ��Ϊһ����������
vector<vector<double>> eigenSpace(vector<vector<double>> eigenVector, int n) {
	vector<vector<double>> r;
	vector<vector<double>> data = transpose(eigenVector);
	for (int i = 0; i < n; i++)
		r.push_back(data[i]);
	return transpose(r);
}

//ѡ���������ɷָ���
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

	cout << "ѡ�����ɷֵ���ֵΪ�� " << THRESHOLD << endl;
	cout << "N = " << k + 1 << endl;

	for (int i = 0; i < 10; i++)
		cout << "��" << i << "����ֵΪ: " << eigenValue[i] << endl;

	return k + 1;
}

//����Euclidian distance
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
		cout << "û�и����ݿ�����Ӧ��label!" << endl;
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
//		cout << "���ļ�ʧ�ܣ�" << endl;
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
		cout << "δ���������ֵ������������";
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

	map<int, vector<double>> personToTotalFace; //��--�������ܺ�
	map<int, int> personToCount;//��--���˵���ͼƬ������
	map<int, vector<double>>::iterator itTotal;
	for (int i = 0; i < data.size(); i++) {
		int j = label[i];

		itTotal = personToTotalFace.find(j);
		//û�ҵ�
		if (itTotal == personToTotalFace.end()) {
			personToTotalFace[j] = projectedFace[i];
			personToCount[j] = 1;
		}
		//�ҵ���
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


//�ȼ��������ͼƬһ��������
//���������������ͼƬһ����ѵ����������һ���˵���
void pca::predict() {
	//��testData��ά
	vector<double> projectedTestFace = (testData - averageFace) * selectedEigen;
	//��testData��ÿ��training�еĽ���ά��face֮���ŷ������
	map<int, double> distanceMap;
	map<int, vector<double>>::iterator it;
	for (it = averageProjectedFace.begin(); it != averageProjectedFace.end(); ++it) {
		distanceMap[it->first] = euclidianDistance(it->second, projectedTestFace);
	}
	//������С���Ǹ���Ϊƥ�����
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
