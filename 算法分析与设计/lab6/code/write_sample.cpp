//将样本写入文件
#include "flowNetwork.cpp"
#include <iostream>
#include <string>
#include <fstream> // 包含文件操作相关的头文件
using namespace std;

int main() {
	for(int i=500;i<=3000;i+=500){
		// 创建一个输出文件流对象
		string filename = "./samples/teamNum_"+to_string(i);
    	ofstream outFile(filename);
    	// 检查文件是否成功打开
	    if (!outFile) {
	        cerr << "无法打开文件" << endl;
	        return 1;
	    }
		//生成随机数据
	    random_data(i);
	    // 将样本数据写入文件
	    for(int i=0;i<n;i++){
	    	outFile<<w[i]<<" "<<r[i]<<"\n";
		}
	    for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				outFile<<g[i][j]<<" ";
			}
			outFile<<"\n";
		}
	    // 关闭文件
	    outFile.close();
	    cout << i << "支球队数据已成功写入文件" << endl;
	}
    return 0;
}