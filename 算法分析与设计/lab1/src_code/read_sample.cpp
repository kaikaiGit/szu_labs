//读取文本文件里的n个样本数值,并返回一个样本数组
#include <string>
#include <fstream>
using namespace std;

int* read_sample(string filePath,int n){
	int *arr = new int[n+5];
	// 打开文本文件
    ifstream inputFile(filePath);
    // 检查文件是否成功打开
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return NULL;
    }
    // 逐行读取文件内容并打印到控制台
    int number;
    int i = 0;
    while (inputFile >> number) {
        if(i==n)break;
        arr[i++] = number;
    }
    // 关闭文件
    inputFile.close();
    return arr;
}

