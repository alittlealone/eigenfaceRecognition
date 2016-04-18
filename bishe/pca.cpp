#include "pca.h"
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <io.h>


bool mySort(double a, double b) {
    return a > b;
}

//void pca::setDatabasePath(string path) {
//    this->databasePath = path;
//}

void pca::setAverageFace() {
    Mat data_tmp;
    data.copyTo(data_tmp);
    Mat sum = data_tmp.row(0);

    for(int i = 1; i < number; i++) {
        sum += data_tmp.row(i);
    }
    this->averageFace = sum / number;
}

void pca::setZeroMeanVec() {
    Mat r(number, pixels, CV_32FC1);
    for(int i = 0; i < number; i++) {
        Mat r_row = r.row(i);
        Mat diff = data.row(i) - averageFace;
        diff.copyTo(r_row);
    }
    this->zeroMeanVec = r;
}

//保留前n个特征值对应的特征向量，组成新的特征空间向量基
//每行为一个特征向量
Mat eigenSpace(Mat eigenVector, int n) {
    Mat r(n, eigenVector.cols, CV_32FC1);
    /*Mat data = eigenVector.t();*/
    for (int i = 0; i < n; i++) {
        Mat r_row = r.row(i);
        eigenVector.row(i).copyTo(r_row);
    }

    return r;
}

int pca::chooseN(Mat eigenValue) {
    float sum = 0;
    for (int i = 0; i < eigenValue.rows; i++) {
        sum += eigenValue.at<float>(i, 0);
    }
    int k;
    float sumK = 0;
    for (k = 0; k < eigenValue.rows; k++) {
        sumK += eigenValue.at<float>(k, 0);
        if (sumK >= THRESHOLD * sum)
            break;
    }

    return k + 1;
}

double euclidianDistance(Mat a, Mat b) {
    float r = 0;
    for (int i = 0; i < a.cols; i++) {
        r += (a.at<float>(0, i) - b.at<float>(0, i)) * (a.at<float>(0, i) - b.at<float>(0, i));
    }
    return r;
}


void getFiles(string path, string exd, vector<string>& files) {
    //文件句柄
    long   hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string pathName, exdName;

    //两个字符串相等，strcmp函数返回0
    if (0 != strcmp(exd.c_str(), ""))
    {
        exdName = "\\*." + exd;
    }
    else
    {
        exdName = "\\*";
    }

    //_findfirst如果失败，则返回-1
    if ((hFile = _findfirst(pathName.assign(path).append(exdName).c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是文件夹中仍有文件夹,迭代之
            //如果不是,加入列表
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

//    else
//        QMessageBox::information(this, tr("error"), tr("Failed to get file!"));
}

pca::pca(string filePath) {
    vector<string> files;
    getFiles(filePath, "BMP", files);

    vector<Mat> originalData;
    int size = files.size();
    for (int i = 0; i < size; i++) {
        string path = files[i];
        Mat image = imread(path, 0);
        originalData.push_back(image);
    }
    this->originalData = originalData;

    number = originalData.size();
    pixels = originalData[0].rows * originalData[0].cols;

    Mat data(number, pixels, CV_32FC1);
    for (int i = 0; i < number; i++) {
        Mat X = data.row(i);
        originalData[i].reshape(1, 1).row(0).convertTo(X, CV_32FC1, 1 / 255.);
    }

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

void pca::setLabel(vector<int> label) {
    this->label = label;
}

void pca::setLabel(string path) {
    vector<int> label;
    if (path == "F:/a/projects/pcaMat/pcaMat/images/ATT") {
        for (int i = 0; i < 63; i++)
            label.push_back(i / 9 + 1);
    }
    else if(path == "F:/a/projects/pcaMat/pcaMat/images/YALE") {
        for (int i = 0; i < 165; i++)
            label.push_back(i / 11 + 1);
    }
    else if(path == "F:/a/projects/pcaMat/pcaMat/images/ORL") {
        for (int i = 0; i < 400; i++)
            label.push_back(i / 10 + 1);
    }
    this->label = label;
//    else
//        QMessageBox::information(this, tr("error"), tr("Failed to set label!"));;
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
    bool ifGetEigen = eigen(covVec, true, eigenValue, eigenVector);
//    if (!ifGetEigen)
//        return -1;
    if(ifGetEigen) {
        eigenVector = (zeroMeanVec.t() * eigenVector.t()).t();//63*10304
        this->selectedEigen = eigenSpace(eigenVector, chooseN(eigenValue));//56*10304
    }

    //63 * 10304    10304 * 56
    this->projectedFace = zeroMeanVec * selectedEigen.t();

//    setLabel(databasePath);
    map<int, Mat> averageProjectedFace;
    map<int, Mat> personToTotalFace;//人--脸向量总和
    map<int, int> personToCount;//人--该人的脸图片总张数
    map<int, Mat>::iterator itTotal;
    for (int i = 0; i < data.rows; i++) {
        int j = label[i];

        itTotal = personToTotalFace.find(j);
        //没找到
        if (itTotal == personToTotalFace.end()) {
            personToTotalFace[j] = projectedFace.row(i);
            personToCount[j] = 1;
        }
        //找到了
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

//先假设输入的图片一定是人脸
//并假设输入的人脸图片一定是训练集中其中一个人的脸
void pca::predict() {
    //把testData降维
    testData = testData.reshape(0, 1);
    testData.convertTo(testData, CV_32FC1, 1 / 255.);

    Mat projectedTestFace = (testData - averageFace) * selectedEigen.t();//1*10304 * 10304*56
    //求testData和每个training中的降过维的face之间的欧拉距离
    map<int, double> distanceMap;
    map<int, Mat>::iterator it;
    for (it = averageProjectedFace.begin(); it != averageProjectedFace.end(); ++it) {
        distanceMap[it->first] = euclidianDistance(it->second, projectedTestFace);
    }
    //距离最小的那个即为匹配的人
    map<int, double>::iterator itDistance = distanceMap.begin();
    int predictedLabel = itDistance->first;
    for (itDistance = distanceMap.begin(); itDistance != distanceMap.end(); ++itDistance) {
        if (itDistance->second < distanceMap[predictedLabel])
            predictedLabel = itDistance->first;
    }
    this->predictedLabel = predictedLabel;
}
