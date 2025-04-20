// 读取地图样本至邻接矩阵matrix中
#include<bits/stdc++.h>
using namespace std;

void init(int matrix[1000][1000]){
	for(int i=1;i<1000;i++){
		for(int j=1;j<1000;j++){
			matrix[i][j] = 0;
		}
	}
}

void read(string filePath,int &max_vNum,int &eNum,int matrix[1000][1000])
{
	init(matrix);//初始化邻接矩阵(置0)
    ifstream file;
    file.open(filePath);
    if(!file.is_open())cout<<"Error!"<<endl;
    string str;
    int a,b;
    while(file>>str){
    	if(str=="p"){
    		file>>str>>max_vNum>>eNum;
		}
		else if(str=="e"){
			file>>a>>b;
			matrix[a][b] = matrix[b][a] = 1;
		}
	}
}
