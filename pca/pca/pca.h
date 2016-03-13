#ifndef PCA_H
#define PCA_H

#include <string>
#include <vector>

#define EPS 0.000001
#define MAXCYCLES 200
#define THRESHOLD 0.99

using namespace std;

class pca {
private:
	string file;
	vector<vector<double>> data;
public:
	pca(string file);
	~pca();
	string getTestFile();
	void setTestFile(string file);
	vector<vector<double>> getData();
	void setData(vector<vector<double>> data);
	vector<vector<double>> readData(string fileName);
	vector<vector<double>> zeroMean(vector<vector<double>> data);
	vector<vector<double>> cov(vector<vector<double>> c);
	int chooseN(vector<double> eigenValue);
	void getEigen(vector<vector<double>> data);
};

#endif