//蛮力法计算所有点对的最短距离
#include <cmath>
typedef std::pair<int,int> PII;

//优化前
//double brute_force(PII *arr,int n){
//	const double INF = 2e7;
//	double ans = INF;
//	for(int i=0;i<n-1;i++){
//		for(int j=i+1;j<n;j++){
//			double dis = getDistance(arr[i],arr[j]);
//			if(dis < ans )ans = dis;
//		}
//	}
//	return ans;
//}


//优化后
double brute_force(PII *arr,int low,int high){
	const double INF = 4e14;
	double ans = INF;
	for(int i=low;i<high;i++){
		for(int j=i+1;j<=high;j++){
			double disX = arr[i].first-arr[j].first;
			if(ans<=disX*disX)continue;
			double disY = arr[i].second-arr[j].second;
			double dis = disX*disX + disY*disY;
			if(dis < ans )ans = dis;
		}
	}
	return sqrt(ans);
}
