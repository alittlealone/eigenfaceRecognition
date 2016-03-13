#include "pca.h"
#include <iostream>

using namespace std;

int main() {
	string fileName = "test.txt";
	pca pcaModel(fileName);
	vector<vector<double>> testData = pcaModel.getData();
	pcaModel.getEigen(testData);
	return 0;
}