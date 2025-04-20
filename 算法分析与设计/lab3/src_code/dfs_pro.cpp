//对称分支剪枝
#include "readSample.cpp"
using namespace std;

int max_vNum,eNum;
int matrix[1000][1000];
int ans = 0;
int color[1000];
const int cNum = 4;

bool check(int index){
	for(int i=1;i<=max_vNum;i++){
		//判断相邻点是否重色
		if(matrix[index][i] && color[index]==color[i])
			return false;
	}
	return true;
}

void dfs_pro(int index){
	if(index > max_vNum){
		ans++;
		for(int i=1;i<=max_vNum;i++){
			cout<<color[i]<<" ";
		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){
		if(i==2 && index==1)break;
		color[index] = i;//涂色
		if(check(index))dfs_pro(index+1);
		color[index] = 0;//回溯
	}
}

int main(){
	string filePath = "./map/test.txt"; //测试样本
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	dfs_pro(1);
	cout<<"一共有 "<<ans*cNum<<" 种涂色方案";
}