//颜色轮换
#include "readSample.cpp"
using namespace std;

int max_vNum,eNum;
int matrix[1000][1000];
int ans = 0;
int color[1000];
int cNum = 4;

struct Vertex{
	int colorAccess[25+1];//邻接点是否存在该颜色，大于等于1为存在，小于1为不存在
    int remainCNum;//可选颜色的数量
    Vertex() {
		remainCNum = cNum; //默认初始化为全部颜色都可选
	}
}vertex[1000];

bool check(int index){
	for(int i=1;i<=max_vNum;i++){
		//判断相邻点是否重色
		if(matrix[index][i] && color[index]==color[i])
			return false;
	}
	return true;
}

int dfs_rotate(int index,int usedColor){
	if(index == max_vNum){
		return vertex[index].remainCNum;
	}
	int s = 0;
	for(int i=1;i<=cNum;i++){
		if(vertex[index].colorAccess[i]>=1)continue;
		int ss = 0;
		vector<int> FCRecover;
		color[index] = i;//涂色
		for(int j=1;j<=max_vNum;j++){//修改邻接点的colorAccess、remainCNum
			if(matrix[index][j] && vertex[j].colorAccess[i]<1){
				FCRecover.push_back(j);
				vertex[j].colorAccess[i] = index;
				vertex[j].remainCNum--;
			}
		}
		bool isNewColor = i > usedColor;//是否为新颜色
		if(check(index)){
			if(isNewColor)
				ss = dfs_rotate(index+1,usedColor+1);		
			else
				ss = dfs_rotate(index+1,usedColor);		
		}
		color[index] = 0;//回溯
		for(int it:FCRecover){
	        vertex[it].colorAccess[i]= 0;
	        vertex[it].remainCNum++;
	    }
		//关键剪枝
		if (isNewColor) {
			s += ss * (cNum - usedColor);
			break;
		}
		s += ss;
	}
	return s;
}

int main(){
	/* 要求一 */
	string filePath = "./map/test.txt"; //测试样本
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	int sum = dfs_rotate(1,0);
	cout<<"一共有 "<<sum<<" 种涂色方案";
	
}