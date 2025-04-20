#include "getDistance.cpp"

//检验算法的正确性（必要不充分条件）
typedef std::pair<int,int> PII;
bool check(PII *arr,int n,double mindis){
	for(int i=0;i<n-1;i++){
		for(int j=i+1;j<n;j++){
			double dis = getDistance(arr[i],arr[j]);
			if(dis<mindis)return false;
		}
	}
	return true;
}