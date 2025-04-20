//分治法计算所有点对的最短距离
#include <algorithm>
#include <cmath>
#include <vector>
#include "brute_force.cpp"
using namespace std;
typedef pair<int,int> PII;

//自定义比较规则1（按照X坐标升序排列）
bool compareX(PII a,PII b){
	return a.first < b.first;
}
//自定义比较规则2（按照Y坐标升序排列）
bool compareY(PII a,PII b){
	return a.second < b.second;
}

double divide_conquer(PII *arr,int low,int high){
	int n = high-low+1;
	//优化1：小规模情况下直接暴力法求解
	if(n<=100)return brute_force(arr,low,high);
	//分治求解左右两部分的最短距离
	int mid = (low+high)/2;//中点归属左边
	double ans = min(divide_conquer(arr,low,mid),divide_conquer(arr,mid+1,high));
	//计算跨越两部分的最短距离
	double left=arr[mid].first-ans, right=arr[mid].first+ans;
	//获得中间部分的点集
	vector<PII> points;
	for(int i=low;i<=high;i++){
		if(arr[i].first<left)continue;
		if(arr[i].first>right)break;
		points.push_back(arr[i]);
	}
	//按Y坐标升序排序
	sort(points.begin(),points.end(),compareY);
	//优化2：对某点与其后1~4个点计算两点间的距离（依赖于Y坐标有序）
	int len = points.size();
	for(int i=0;i<len-1;i++){
		for(int j=i+1;j<=i+4&&j<len;j++){
			double disY = points[j].second-points[i].second;
			if(disY >= ans)break;//优化3：剪枝（依赖于Y坐标有序）
			double disX = points[j].first-points[i].first;
			double dis = sqrt(disX*disX + disY*disY);
			if(dis<ans)ans = dis; //更新最小值
		}
	}
	return ans;
}

