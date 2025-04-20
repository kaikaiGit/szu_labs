//读取随机样本 并 返回相应大小的pair数组
#include <string>
#include <fstream>
using namespace std;

pair<int,int>* read_sample(string filePath,int n){
	//分配一块大小约为n的数组空间
	pair<int,int> *arr = new pair<int,int>[n+5];
	// 打开文本文件
    ifstream inputFile(filePath);
    // 检查文件是否成功打开
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return NULL;
    }
    // 逐行读取文件内容并打印到控制台
    int a,b;
    int i = 0;
    while (inputFile >> a >> b) {
        arr[i].first = a;
        arr[i].second = b;
        i++;
        if(i==n)break;
    }
    // 关闭文件
    inputFile.close();
    return arr;
}
