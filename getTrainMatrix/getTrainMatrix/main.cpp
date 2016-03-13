#include "bitmap.h"
#include <iostream>
#include <io.h>

using namespace std;

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

vector<vector<int>> getTrainData(vector<string> files) {
	vector<vector<int>> r;
	
	int size = files.size();
	for (int i = 0; i < size; i++) {
		string path = files[i];
		bitmap *image = new bitmap(path);
		vector<int> imageData = image->getData();
		image->closeFile();
		r.push_back(imageData);
	}

	return r;
}

int main() {
	char * filePath = "./images/ATT";
	vector<string> files;

	getFiles(filePath, "BMP", files);

	vector<vector<int>> trainData = getTrainData(files);

	cout << "ѵ�����ݹ��������� " << trainData.size() << endl;
	cout << "ÿ�������� " << trainData[0].size() << endl;
	/*cout << "�����һ��ǰ10�����ݣ� " << endl;
	for (int i = 0; i < 10; i++)
		cout << trainData[0][i] << " ";
	cout << endl;
	cout << "����ڶ���ǰ10�����ݣ� " << endl;
	for (int i = 0; i < 10; i++)
		cout << trainData[1][i] << " ";
	cout << endl;*/

	system("pause");
}