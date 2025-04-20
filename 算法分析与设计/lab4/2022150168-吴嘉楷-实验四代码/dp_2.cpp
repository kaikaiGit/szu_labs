/*动态规划算法二求解鸡蛋掉落问题 */
#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;

int dp[10005][10005];
int dp_solve_2(int e,int f){
	for(int i=1;i<=f;i++){
		for(int j=1;j<=e;j++){
			dp[j][i] = dp[j][i-1] + dp[j-1][i-1] + 1;
			if(dp[j][i] >= f)return i;
		}
	}
	return f;
}
const int N = 1e4;

int main(){
	int e = 100;
	cout<<"固定鸡蛋数为："<<e<<"\n";
	for(int f=50000;f<=100000;f+=10000){
		memset(dp,0,sizeof(dp));
		clock_t start = clock();
		dp_solve_2(e,f);
    	clock_t end = clock();
    	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
    	cout<<"当楼层数为："<<f<<"时，算法耗时为："<<diff<<"ms。"<<endl;
	}
}