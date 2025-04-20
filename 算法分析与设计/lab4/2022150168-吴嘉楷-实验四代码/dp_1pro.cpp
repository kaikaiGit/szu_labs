/*动态规划算法一求解鸡蛋掉落问题  ————使用二分法优化*/
#include<iostream>
#include<cstring>
#include<ctime>
using namespace std;

int dp[10005][10005];
int dp_solve_pro(int f,int e){
	//初始化
	for(int i=1;i<=f;i++)dp[i][1] = i;
	for(int i=1;i<=e;i++)dp[1][i] = 1;
	
	for(int i=2;i<=f;i++){
		for(int j=2;j<=e;j++){
			int l = 1, r = i;
			while(l+1 < r){
				int mid = (l+r)/2;
				int t1 = dp[mid-1][j-1];
				int t2 = dp[i-mid][j];
				if(t1 < t2)l = mid;
				else if(t1 > t2)r = mid;
				else l = r = mid;
			}
			
			dp[i][j] = 1 + min( max(dp[l-1][j-1],dp[i-l][j]) , max(dp[r-1][j-1],dp[i-r][j]) );
		}
	}
	return dp[f][e];
}

int main(){
//	int e = 100;
//	cout<<"固定鸡蛋数为："<<e<<"\n";
//	for(int f=50000;f<=100000;f+=10000){
//		memset(dp,0,sizeof(dp));
//		clock_t start = clock();
//		dp_solve_pro(f,e);
//    	clock_t end = clock();
//    	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
//    	cout<<"当楼层数为："<<f<<"时，算法耗时为："<<diff<<"ms。"<<endl;
//	}

	int f = 10000;
	cout<<"固定楼层数为："<<f<<"\n";
	for(int e=5000;e<=10000;e+=1000){
		memset(dp,0,sizeof(dp));
		clock_t start = clock();
		dp_solve_pro(e,f);
    	clock_t end = clock();
    	double diff = (double)(end - start) *1000 / CLOCKS_PER_SEC;
    	cout<<"当鸡蛋数为："<<e<<"时，算法耗时为："<<diff<<"ms。"<<endl;
	}
}
