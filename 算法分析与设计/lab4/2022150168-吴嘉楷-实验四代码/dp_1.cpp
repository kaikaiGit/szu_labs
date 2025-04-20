/*动态规划算法一求解鸡蛋掉落问题*/
#include<iostream>
#include<ctime>
using namespace std;

int dp[100005][105];
int dp_solve(int f,int e){
	//初始化
	for(int i=1;i<=f;i++)dp[i][1] = i;
	for(int i=1;i<=e;i++)dp[1][i] = 1;
	
	for(int i=2;i<=f;i++){
		for(int j=2;j<=e;j++){
			dp[i][j] = i;
			for(int k=1;k<=i;k++){
				dp[i][j] = min( dp[i][j] , max(dp[k-1][j-1],dp[i-k][j]) + 1);
			}
		}
	}
	return dp[f][e];
}

int main(){
	int e = 100;
	cout<<"固定鸡蛋数为："<<e<<"\n";
	for(int f=100;f<=100000;f*=10){
		clock_t start = clock();
		dp_solve(f,e);
    	clock_t end = clock();
    	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
    	cout<<"当楼层数为："<<f<<"时，算法耗时为："<<diff<<"ms。"<<endl;
	}
}

