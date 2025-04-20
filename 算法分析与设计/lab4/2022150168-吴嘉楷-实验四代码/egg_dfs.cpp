/*蛮力法求解鸡蛋掉落问题*/
#include<iostream>
using namespace std;


int mem[10005][100];
int dfs(int f,int e){
	if(f==0)return 0;
	if(e==1)return f;
	if(mem[f][e])return mem[f][e];
	
	int res = f;
	for(int i=1;i<=f;i++){
		res = min( res , max(dfs(i-1,e-1),dfs(f-i,e)) + 1);
	}
	return mem[f][e] = res;
}


