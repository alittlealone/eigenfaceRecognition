#ifndef PCA_H
#define PCA_H

#include <string>
#include <vector>
#include <map>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define EPS 0.000001                         //������ֵ��ֵ
#define MAXCYCLES 20000                      //������ֵ���ѭ������
#define THRESHOLD 0.99                       //ѡ�����ɷֵ���ֵ


class pca {
private:
	vector<Mat> originalData;
	Mat data;
	int number;
	int pixels;
	vector<int> label;
	Mat testData;
	Mat averageFace;
	Mat zeroMeanVec;
	Mat selectedEigen;
	Mat projectedFace;
	map<int, Mat> averageProjectedFace;
	int predictedLabel;

public:
	pca(string path);
	~pca();

	int getPixels();
	void setTestData(Mat data);
	vector<Mat> getOriginalData();
	void setOriginalData(vector<Mat> originalData);
	Mat getData();
	void setData(Mat data);
	void setLabel(string path);
	void setAverageFace();
	void setZeroMeanVec();
	
	int chooseN(Mat eigenValue);
	int getPredictedLabel();

	void train();
	void predict();
};

#endif