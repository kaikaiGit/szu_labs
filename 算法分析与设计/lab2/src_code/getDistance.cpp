#include <cmath>
typedef std::pair<int,int> PII;

//计算两点之间的距离
double getDistance(PII a,PII b){
	double disX = a.first-b.first;
	double disY = a.second-b.second;
	return  sqrt(disX*disX + disY*disY);
}
