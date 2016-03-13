#ifndef PCA_H
#define PCA_H

#include <string>
#include <vector>
#include <map>

#define EPS 0.000001                         //求特征值阈值
#define MAXCYCLES 20000                      //求特征值最大循环次数
#define THRESHOLD 0.99                       //选择主成分的阈值

using namespace std;

class pca {
private:
	vector<vector<int>> data;
	vector<int> label;
	vector<int> testData;
	vector<double> averageFace;
	vector<vector<double>> zeroMeanVec;
	vector<vector<double>> selectedEigen;
	vector<vector<double>> projectedFace;
	map<int, vector<double>> averageProjectedFace;
	int predictedLabel;
public:
	pca(vector<vector<int>> data);
	~pca();

	//string getTestFile();
	void setTestData(vector<int> data);
	vector<vector<int>> getData();
	void setData(vector<vector<int>> data);
	void setLabel(string path);
	//vector<vector<double>> readData(string fileName);
	void setAverageFace();
	void setZeroMeanVec();
	bool eigen(vector<vector<double>> c, vector<vector<double>>& eigenVector, vector<double>& eigenValue);
	vector<vector<double>> cov(vector<vector<double>> c);
	int chooseN(vector<double> eigenValue);
	int getPredictedLabel();

	void train();
	void predict();
};

#endif