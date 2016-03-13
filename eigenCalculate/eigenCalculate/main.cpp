#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#define EPS        0.0000001
#define MAXCYCLES  20000

bool mySort(double a, double b) {
	return a > b;
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

	for (int i = 0; i < n; i++)
		eigenValue.push_back(c[i][i]);

	/*for (int j = 0; j < n; j++) {
		double sumVec = 0;
		for (int i = 0; i < n; i++)
			sumVec += eigenVector[i][j];
		if (sumVec < 0) {
			for (int i = 0; i < n; i++)
				eigenVector[i][j] *= -1;
		}
	}*/

	return true;
}

vector<vector<double>> readData(string fileName) {
	ifstream in;
	vector<vector<double> > data;
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


int main() {
	vector<vector<double>> c;
	vector<vector<double>> eigenVector;
	vector<double> eigenValue;
	ofstream eValue("eigenValue.txt");
	ofstream eVector("eigenVector.txt");
	c = readData("C:/Users/Administrator/Desktop/pca_python/scripts/--被求特征值的矩阵.txt");
	bool getEigen = eigen(c, eigenVector, eigenValue);
	if (!getEigen)
		cout << "Oops! Something goes wrong!" << endl;
	else {
		for (int i = 0; i < eigenValue.size(); i++)
			eValue << eigenValue[i] << endl;
		for (int i = 0; i < eigenVector.size(); i++) {
			for (int j = 0; j < eigenVector[0].size(); j++)
				eVector << eigenVector[i][j] << " ";
			eVector << endl;
		}
	}

	sort(eigenValue.begin(), eigenValue.end(), mySort);
	ofstream seValue("sortedEigenValue.txt");
	for (int i = 0; i < eigenValue.size(); i++)
		seValue << eigenValue[i] << endl;

	return 0;
}