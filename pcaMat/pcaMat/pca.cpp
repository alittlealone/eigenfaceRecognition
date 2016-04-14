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
	Mat sum = data.row(0);

	ofstream fout("./sumFace.txt");
	for (int i = 0; i < sum.cols; i++)
		fout << sum.at<float>(0, i) << " ";

	for(int i = 1; i < number; i++) {
		sum += data.row(i);
	}
	this->averageFace = sum / number;

	/*ofstream fout("./sumFace.txt");
	for (int i = 0; i < sum.cols; i++)
		fout << sum.at<float>(0, i) << " ";*/
}

void pca::setZeroMeanVec() {
	Mat r(number, pixels, CV_32FC1);
	for(int i = 0; i < number; i++) {
		r.row(i) = data.row(i) - averageFace;
	}
	this->zeroMeanVec = r;

	ofstream fout("./zeroMeanVec.txt");
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < pixels; j++)
			fout << r.at<float>(i, j) << " ";
		fout << endl;
	}

}


//��AΪԭ�������ֵ����ľ���(M * N^2)
//��Ҫ��A * A^T (N^2 * n^2)����������
//���Ƶ�����ȼ�����A^T * (A * A^T ����������)
//��������A * A^T���ȼ�����cov(A, A^T)���ȼ���cov(data, data^T)
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

//���ſɱ��㷨��Э�����������ֵ����������
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

//����ǰn������ֵ��Ӧ����������������µ������ռ�������
//ÿ��Ϊһ����������
Mat eigenSpace(Mat eigenVector, int n) {
	Mat r(n, eigenVector.cols, CV_32FC1);
	Mat data = eigenVector.t();
	for (int i = 0; i < n; i++) {
		r.row(i) = eigenVector.row(i);
	}
	return r.t();
}

//ѡ���������ɷָ���
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
//	cout << "ѡ�����ɷֵ���ֵΪ�� " << THRESHOLD << endl;
//	cout << "N = " << k + 1 << endl;
//
//	for (int i = 0; i < 10; i++)
//		cout << "��" << i << "����ֵΪ: " << eigenValue[i] << endl;
//
//	return k + 1;
//}

int pca::chooseN(Mat eigenValue) {
	float sum = 0;
	for (int i = 0; i < eigenValue.rows; i++) {
		cout << i << "��" << eigenValue.at<float>(i, 0) << endl;
		sum += eigenValue.at<float>(i, 0);
	}
	int k;
	float sumK = 0;
	for (k = 0; k < eigenValue.rows; k++) {
		sumK += eigenValue.at<float>(k, 0);
		if (sumK >= THRESHOLD * sum)
			break;
	}

	cout << "ѡ�����ɷֵ���ֵΪ�� " << THRESHOLD << endl;
	cout << "N = " << k + 1 << endl;

	for (int i = 0; i < 10; i++)
		cout << "��" << i << "����ֵΪ: " << eigenValue.at<double>(i, 0) << endl;

	return k + 1;
}

//����Euclidian distance
//double euclidianDistance(vector<double> a, vector<double> b) {
//	double r = 0;
//	for (int i = 0; i < a.size(); i++)
//		r += (a[i] - b[i]) * (a[i] - b[i]);
//	return r;
//}

double euclidianDistance(Mat a, Mat b) {
	float r = 0;
	//���ܲ��ԣ���֪�����ݽṹ������
	for (int i = 0; i < a.cols; i++) {
		r += (a.at<float>(0, i) - b.at<float>(0, i)) * (a.at<float>(0, i) - b.at<float>(0, i));
	}
	return r;
}


void getFiles(string path, string exd, vector<string>& files) {
	//�ļ����
	long   hFile = 0;
	//�ļ���Ϣ
	struct _finddata_t fileinfo;
	string pathName, exdName;

	//�����ַ�����ȣ�strcmp��������0
	if (0 != strcmp(exd.c_str(), ""))
	{
		exdName = "\\*." + exd;
	}
	else
	{
		exdName = "\\*";
	}

	//_findfirst���ʧ�ܣ��򷵻�-1
	if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//������ļ����������ļ���,����֮
			//�������,�����б�
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


static Mat asRowMatrix(InputArrayOfArrays src, int rtype, double alpha = 1, double beta = 0) {
	// make sure the input data is a vector of matrices or vector of vector
	if (src.kind() != _InputArray::STD_VECTOR_MAT && src.kind() != _InputArray::STD_VECTOR_VECTOR) {
		string error_message = "The data is expected as InputArray::STD_VECTOR_MAT (a std::vector<Mat>) or _InputArray::STD_VECTOR_VECTOR (a std::vector< vector<...> >).";
		CV_Error(CV_StsBadArg, error_message);
	}
	// number of samples
	size_t n = src.total();
	// return empty matrix if no matrices given
	if (n == 0)
		return Mat();
	// dimensionality of (reshaped) samples
	size_t d = src.getMat(0).total();
	// create data matrix
	Mat data((int)n, (int)d, rtype);
	// now copy data
	for (unsigned int i = 0; i < n; i++) {
		// make sure data can be reshaped, throw exception if not!
		if (src.getMat(i).total() != d) {
			string error_message = format("Wrong number of elements in matrix #%d! Expected %d was %d.", i, d, src.getMat(i).total());
			CV_Error(CV_StsBadArg, error_message);
		}
		// get a hold of the current row
		Mat xi = data.row(i);
		// make reshape happy by cloning for non-continuous matrices
		if (src.getMat(i).isContinuous()) {
			src.getMat(i).reshape(1, 1).convertTo(xi, rtype, alpha, beta);
		}
		else {
			src.getMat(i).clone().reshape(1, 1).convertTo(xi, rtype, alpha, beta);
		}
	}
	return data;
}

pca::pca(string filePath) {
	vector<string> files;
	getFiles(filePath, "BMP", files);

	vector<Mat> originalData;
	int size = files.size();
	for (int i = 0; i < size; i++) {
		string path = files[i];
		Mat image = imread(path);
		originalData.push_back(image);
	}
	this->originalData = originalData;

	/*Mat a = originalData[0];
	ofstream fout("./originalData0.txt");*/
	/*for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++)
			fout << a.at<unsigned char>(i, j) << " ";
		fout << endl;
	}*/
	/*fout << ' ' << a << endl;*/

	number = originalData.size();
	pixels = originalData[0].rows * originalData[0].cols;
	
	/*Mat data(number, pixels, CV_32FC1);*/

	/*Mat b = originalData[0].reshape(0, 1);
	data.row(0) = b;
	ofstream fout("./data.txt");
	fout << ' ' << b << endl;*/

	vector<Mat> data_tmp;
	for (int i = 0; i < number; i++) {
		/*Mat data_row = data.row(i);
		originalData[i].reshape(1, 1).row(0).convertTo(data_row, CV_32FC1, 1 / 255.);*/
		Mat data_row = originalData[i].reshape(0, 1);
		data_tmp.push_back(data_row);
	}
	Mat data = asRowMatrix(data_tmp, CV_32FC1);

	ofstream fout("./data.txt");
	fout << ' ' << data.row(0) << endl;

	/*for (int i = 0; i < number; i++) {
		for (int j = 0; j < pixels; j++) {
			data.at<unsigned char>(i, j) = data_tmp[i].at<unsigned char>(0, j);
		}
	}*/

	//Mat a = originalData[0].reshape(0, 1);
	/*ofstream fout("./data.txt");
	fout << ' ' << data.row(0) << endl;*/

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
		cout << "û�и����ݿ�����Ӧ��label!" << endl;
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
		cout << "δ���������ֵ������������";
	else {
		for (int i = 0; i < eigenVector.rows; i++) {
			for (int j = 0; j < eigenVector.cols; j++) {
				cout << eigenVector.at<float>(i, j) << " ";
			}
			cout << endl;
		}
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
	map<int, Mat> averageProjectedFace;
	map<int, Mat> personToTotalFace;//��--�������ܺ�
	map<int, int> personToCount;//��--���˵���ͼƬ������
	map<int, Mat>::iterator itTotal;
	for (int i = 0; i < data.rows; i++) {
		int j = label[i];

		itTotal = personToTotalFace.find(j);
		//û�ҵ�
		if (itTotal == personToTotalFace.end()) {
			personToTotalFace[j] = projectedFace.row(i);
			personToCount[j] = 1;
		}
		//�ҵ���
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

//�ȼ��������ͼƬһ��������
//���������������ͼƬһ����ѵ����������һ���˵���
void pca::predict() {
	//��testData��ά
	Mat projectedTestFace = (testData - averageFace) * selectedEigen;
	//��testData��ÿ��training�еĽ���ά��face֮���ŷ������
	map<int, double> distanceMap;
	map<int, Mat>::iterator it;
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
