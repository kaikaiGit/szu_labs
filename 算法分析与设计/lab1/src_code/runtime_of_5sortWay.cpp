//冒泡排序算法(升序）
#include<iostream>
#include<ctime>
#include "read_sample.cpp"
#include "check.cpp"
#include "bubble_sort.cpp" 	//引入冒泡排序
#include "select_sort.cpp"	//引入选择排序
#include "insert_sort.cpp"	//引入插入排序
#include "merge_sort.cpp"	//引入合并排序
#include "quick_sort.cpp"	//引入快速排序
using namespace std;

int main(){
	int n = 50000;
	cout<<"固定每组样本容量为"<<n<<"。\n";
	//样本文件部分路径
	string basePath = "./20pieces_of_samples/sample_";
	double sum;
	
	//——————————————统计20组随机样本的运行时间之冒泡排序——————————————
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=20;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,n);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	//排序算法
		bubble_sort(arr,n);
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
		delete []arr; //手动清理空间
	}
	cout<<"冒泡排序的平均运行时间为:"<<sum/20<<"ms\n\n";
	
	//——————————————统计20组随机样本的运行时间之选择排序——————————————
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=20;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,n);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	//排序算法
		select_sort(arr,n);
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
		delete []arr; //手动清理空间
	}
	cout<<"选择排序的平均运行时间为:"<<sum/20<<"ms\n\n";
	
	//——————————————统计20组随机样本的运行时间之插入排序——————————————
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=20;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,n);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	//排序算法
		insert_sort(arr,n);
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
		delete []arr; //手动清理空间
	}
	cout<<"插入排序的平均运行时间为:"<<sum/20<<"ms\n\n";
	
	//——————————————统计20组随机样本的运行时间之合并排序——————————————
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=20;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,n);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	//排序算法
		merge_sort(arr,0,n-1);
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
		delete []arr; //手动清理空间
	}
	cout<<"合并排序的平均运行时间为:"<<sum/20<<"ms\n\n";

	//——————————————统计20组随机样本的运行时间之快速排序——————————————
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=20;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,n);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	//排序算法
		(arr,0,n-1);
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start) / CLOCKS_PER_SEC * 1000;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本的运行时间为："<<duration<<"ms\n";
		delete []arr; //手动清理空间
	}
	cout<<"快速排序的平均运行时间为:"<<sum/20<<"ms\n\n";
}