#include <iostream>
#include <vector>
#include <string>
#include "dirent.h"

using namespace std;

vector<string> getFiles(string PATH) {
	vector<string> files;
	struct dirent *ptr;
	DIR *dir;
	dir = opendir(PATH.c_str());
	while ((ptr = readdir(dir)) != NULL)
	{

		//跳过'.'和'..'两个目录
		if (ptr->d_name[0] == '.')
			continue;
		//cout << ptr->d_name << endl;
		files.push_back(ptr->d_name);
	}
	closedir(dir);
	return files;
}

int main()
{
	//struct dirent *ptr;

	/*DIR *dir;
	string PATH = "F:\\face\\ATT";
	dir = opendir(PATH.c_str());*/
	vector<string> files;
	files = getFiles("F:\\face\\ATT");
	cout << "文件列表: " << endl;
	//while ((ptr = readdir(dir)) != NULL)
	//{

	//	//跳过'.'和'..'两个目录
	//	if (ptr->d_name[0] == '.')
	//		continue;
	//	//cout << ptr->d_name << endl;
	//	files.push_back(ptr->d_name);
	//}

	for (int i = 0; i < files.size(); ++i)
	{
		cout << files[i] << endl;
	}

	//closedir(dir);

	system("pause");

	return 0;
}