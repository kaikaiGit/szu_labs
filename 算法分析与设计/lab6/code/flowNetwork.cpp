//流网络图
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // 包含rand和srand函数
#include <ctime>   // 包含time函数
#include <fstream> // 包含文件操作相关的头文件
#include <chrono> // 包含高精度计时相关的头文件
using namespace std;

const int INF = 1e9; //代表无穷大
const int max_Num = 3e3;

struct EDGE
{
    int for_point;  // 指向的节点
    int capacity;   // 路径容量
    int index;		// 指向节点的第index条反向边
    int flow;       // 当前流量
};

vector<EDGE> edge[max_Num+5];
int visit[max_Num+5];
string teams[4] = {"Atlanta","Philly","New York","Montreal"};
int n = 4;
int w[max_Num+5] = {83,80,78,77};
int r[max_Num+5] = {8,3,6,3};
int g[max_Num+3][max_Num+3] = {
		{0,1,6,1},
		{1,0,0,2},
		{6,0,0,0},
		{1,2,0,0}
	};
int s = 0; // 源点
int totalGames; //比赛总场次
int t; // 汇点

//添加边的函数
void addEdge(int s, int e, int capacity){
	//正向边
	EDGE a = {e,capacity,static_cast<int>(edge[e].size()),0};
	//反向边
	EDGE b = {s,0,static_cast<int>(edge[s].size()),0};
	edge[s].push_back(a);
	edge[e].push_back(b);
}

//构建流网络图，返回false则说明被提前淘汰，无需构建流网络
bool createFlowNetwork(int x){
	s = 0;
    totalGames = (n - 1) * (n - 2) / 2; //n-1支队伍两两对战(排除掉队伍x）
    t = totalGames + n + 1; // 汇点
    int gameIndex = 1;
    
    // 重置边
    for (int i = 0; i < max_Num; i++) {
        edge[i].clear();
    }
    
    for (int i = 0; i < n; i++) {
        if (i == x) continue;
        // 平凡淘汰
        if (w[x] + r[x] - w[i] < 0)return false;
        for (int j = i + 1; j < n; j++) {
            if (j == x) continue;
            // 添加源点到比赛点的边
            addEdge(s, gameIndex, g[i][j]);
			// 比赛点到队伍点的边
            addEdge(gameIndex, totalGames + i + 1, INF);
            addEdge(gameIndex, totalGames + j + 1, INF);
            gameIndex++;
        }
        // 添加队伍点到汇点的边
        addEdge(totalGames + i + 1, t, w[x] + r[x] - w[i]);
    }
    return true;
}

void random_data(int num){
	int max_win = 90,min_win = 70;
	n = num;
	// 使用当前时间作为随机数生成器的种子
    srand(static_cast<unsigned int>(std::time(nullptr)));
    // 生成n个随机胜场
    for (int i = 0; i < n; ++i) {
    	w[i] = rand()%(max_win-min_win) + min_win;
    }
    //初始化
    for(int i=0;i<n;i++){
    	r[i] = 0;
    	for(int j=0;j<n;j++){
    		g[i][j] = 0;
		}
	}
    // 生成赛程二维数组
    for(int i=0;i<n;i++){
    	for(int j=i+1;j<n;j++){ 
    		int rand_num = rand() % n;
    		rand_num = rand_num<=(n-6) ? 0 : rand_num-(n-6);
    		g[i][j] = rand_num;
    		g[j][i] = rand_num;
    		r[i] += rand_num;
    		r[j] += rand_num;
		}
	}
	/*for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<g[i][j]<<" ";
		}
		cout<<" -- w[i]:"<<w[i]<<"  r[i]:"<<r[i]<<endl;
	}*/
}

void read_sample(string filePath, int num){
	// 打开要读取的文件
    ifstream inFile(filePath);
    // 检查文件是否成功打开
    if (!inFile) {
        std::cerr << "无法打开文件" << std::endl;
        return;
    }
	for(int i=0;i<num;i++){
	    inFile>>w[i]>>r[i];
	}
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
			inFile>>g[i][j];
		}
	}
}