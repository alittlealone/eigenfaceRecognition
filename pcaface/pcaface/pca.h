#ifndef PCA_H
#define PCA_H

#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>

using namespace cv;

#define EPS 0.000001                         //求特征值阈值
#define MAXCYCLES 20000                      //求特征值最大循环次数
#define THRESHOLD 0.99                       //选择主成分的阈值

using namespace std;

class pca {
private:
	//vector<Mat> data;
	vector<vector<int>> data;
	//vector<int> label;
	vector<int> label;
	//Mat testData;
	vector<int> testData;
	//Mat averageFace;
	vector<double> averageFace;
	//vector<Mat> zeroMeanVec;
	vector<vector<double>> zeroMeanVec;
	//Mat selectedEigen;
	vector<vector<double>> selectedEigen;
	//Mat projectedFace;
	vector<vector<double>> projectedFace;
	//map<int, Mat> averageProjectedFace;
	map<int, vector<double>> averageProjectedFace;
	//int predictedLabel;
	int predictedLabel;
public:
	//pca(vector<Mat> data);
	pca(vector<vector<int>> data);
	//pca();
	~pca();

	//void setTestData(Mat data);
	void setTestData(vector<int> data);
	//vector<Mat> getData();
	vector<vector<int>> getData();
	//void setData(vector<Mat> data);
	void setData(vector<vector<int>> data);
	//void setLabel(string path);
	void setLabel(string path);
	//void setAverageFace();
	void setAverageFace();
	//void setZeroMeanVec();
	void setZeroMeanVec();
	//bool eigen(vector<Mat> c, vector<Mat>& eigenVector, vector<double>& eigenValue);
	bool eigen(vector<vector<double>> c, vector<vector<double>>& eigenVector, vector<double>& eigenValue);
	//vector<Mat> cov(vector<Mat> c);
	vector<vector<double>> cov(vector<vector<double>> c);
	//int chooseN(Mat eigenValue);
	int chooseN(vector<double> eigenValue);
	//int getPredictLabel();
	int getPredictedLabel();

	//void train();
	void train();
	//void predict();
	void predict();
};

#endif