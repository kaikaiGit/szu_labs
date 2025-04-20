#include <iostream>
#include <ctime>
#include "check.cpp"
#include "divide_conquer.cpp"
#include "read_samples.cpp"
typedef pair<int,int> PII;
using namespace std;


//蛮力法和分治法的对比
int main(){
	string basePath = "10groupsOfSample/samples";
	double sum = 0;
	
	for(int n=1e5;n<=1e6;n+=1e5){
		cout<<"输入规模为"<<n<<"时：\n";
		//——————————————统计10组随机样本的运行时间之蛮力法——————————————
		//初始化总运行时间
		sum = 0;
		for(int i=1;i<=10;i++){
			string filePath = basePath + to_string(i) + ".txt";
			PII *arr=read_sample(filePath,n);
			// 获取程序开始时的时钟周期数
	    	clock_t start = clock();
	    	//蛮力算法
			double ans = brute_force(arr,0,n-1);
			// 获取程序结束时的时钟周期数
	    	clock_t end = clock();
	    	// 计算程序运行时间（单位：毫秒）
	    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
	    	sum += duration;
			cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
			delete []arr; //手动清理空间
		}
		cout<<"蛮力法的平均运行时间为:"<<sum/10<<"ms\n";
		cout<<"——————————————————————————————————————\n";
		//——————————————统计10组随机样本的运行时间之分治法——————————————
		//初始化总运行时间
		sum = 0;
		for(int i=1;i<=10;i++){
			string filePath = basePath + to_string(i) + ".txt";
			PII *arr=read_sample(filePath,n);
			//按照X坐标进行排序
			sort(arr,arr+n,compareX);
			// 获取程序开始时的时钟周期数
	    	clock_t start = clock();
	    	//分治算法
			double ans = divide_conquer(arr,0,n-1);
			// 获取程序结束时的时钟周期数
	    	clock_t end = clock();
	    	// 计算程序运行时间（单位：毫秒）
	    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
	    	sum += duration;
			cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
			delete []arr; //手动清理空间
		}
		cout<<"分治法的平均运行时间为:"<<sum/10<<"ms\n\n";
	}
	
}