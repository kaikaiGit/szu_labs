/*动态规划算法二求解鸡蛋掉落问题  ————优化空间复杂度*/
#include<iostream>
#include<cstring>
#include <chrono>
#include<ctime>
using namespace std;
using ll = long long;

int dp[400000005];
const int N = 1e8;
ll dp_solve_2pro(int e,int f){
	for(ll i=1;i<=f;i++){
		for(ll j=e;j>=1;j--){
			dp[j] = dp[j] + dp[j-1] + 1;
			if(dp[j] >= f)return i;
		}
	}
	return f;
}

int main(){
//	int e = 4*N;
//	cout<<"固定鸡蛋数为："<<e<<"\n";
//	for(int f=N;f<=5*N;f+=N){
//		memset(dp,0,sizeof(dp));
//		clock_t start = clock();
//		dp_solve_2pro(e,f);
//    	clock_t end = clock();
//    	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
//    	cout<<"当楼层数为："<<f<<"时，算法耗时为："<<diff<<"ms。"<<endl;
//	}
	
//	int f = N/10;
//	cout<<"固定楼层数为："<<f<<"\n";
//	for(int e=N;e<=4*N;e+=N){
//		memset(dp,0,sizeof(dp));
//		clock_t start = clock();
//		dp_solve_2pro(e,f);
//    	clock_t end = clock();
//    	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
//    	cout<<"当鸡蛋数为："<<e<<"时，算法耗时为："<<diff<<"ms。"<<endl;
//	}


	/*尝试超大规模*/
	int e = 4*N;
	long long f = 1e17;
	cout<<"固定鸡蛋数为："<<e<<"\n";
	clock_t start = clock();
	dp_solve_2pro(e,f);
	clock_t end = clock();
	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
	cout<<"当楼层数为："<<f<<"时，算法耗时为："<<diff<<"ms。"<<end;
	return 0;
}