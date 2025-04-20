//topK问题算法
//以规模为10万的数据量进行探究,每次取算法在6组样本上的运行时间的平均值
#include<iostream>
#include<ctime>
#include<queue>
#include "read_sample.cpp"
#include "checkTopK.cpp"

// 分割函数，将数组分成左右两部分，并返回基准元素的索引位置
int part(int *arr,int low,int high){
	int pivot = arr[low]; //先以第一个元素作为基准数
	while(low<high){
		//比基准数小的移动到左边
		while(low<high && arr[high]>=pivot)
			high--;
		arr[low] = arr[high];
		//比基准数大的移动到右边
		while(low<high && arr[low]<=pivot)
			low++;
		arr[high] = arr[low];
	}
	arr[low] = pivot; //基准数放到最终位置
	return low;
}
//不完全快速排序
//arr为数组名，low为待排序序列的起始下标，high为待排序序列结尾元素下标
void quickSort(int *arr,int low,int high){
	if(low < high){
		int pivotIdx = part(arr,low,high);//获取基准数的下标
		if(high-(pivotIdx+1) < 10)quickSort(arr,low,pivotIdx-1); //对左子数组进行排序
		quickSort(arr,pivotIdx+1,high); //对右子数组进行排序
	}
}

int main(){
	//样本文件部分路径
	string basePath = "./20pieces_of_samples/sample_";
	//样本规模size = 1e6
	const int size = 1e6;
	//算法在6组样本上的总运行时间
	double sum;
	
	cout<<"————————topK的解决方案一：进行10趟冒泡排序————————\n";
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=6;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,size);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	
    	//topK算法的解决方案一
		int *topArr = new int[15];
		for(int i=1;i<=10;i++){ //第i趟排序
			for(int j=0;j<size-i;j++){ //下标为j的数
				if(arr[j]>arr[j+1]){
					int temp=arr[j];
					arr[j]=arr[j+1];
					arr[j+1]=temp;
				}
			}
			topArr[i-1] = arr[size-i];
		}
		
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本："<<duration<<"ms "
		<<(checkTopK(arr,size,topArr)?"true":"false")<<"\n";
		//手动清理空间
		delete []arr; 
		delete []topArr;
	}
	cout<<"解决方案一的平均运行时间为:"<<sum/6<<"ms\n\n";
	
	cout<<"————————topK的解决方案二：进行10趟选择排序————————\n";
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=6;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,size);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	
    	//topK算法的解决方案二
		int *topArr = new int[15];
		for(int i=0;i<=9;i++){ //第i+1趟排序(降序)
			int maxPos = i;
			for(int j=i+1;j<size;j++){
				if(arr[j]>arr[maxPos])
					maxPos = j;
			}
			swap(arr[i],arr[maxPos]);
			topArr[i] = arr[i];
		}
		
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本："<<duration<<"ms "
		<<(checkTopK(arr,size,topArr)?"true":"false")<<"\n";
		//手动清理空间
		delete []arr; 
		delete []topArr;
	}
	cout<<"解决方案二的平均运行时间为:"<<sum/6<<"ms\n\n";
	
	cout<<"————————topK的解决方案三：对数据进行快速排序————————\n";
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=6;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,size);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	
    	//topK算法的解决方案三
		int *topArr = new int[15];
		quickSort(arr,0,size-1);
		for(int i=0;i<10;i++){
			topArr[i] = arr[size-1-i];
		}
		
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本："<<duration<<"ms "
		<<(checkTopK(arr,size,topArr)?"true":"false")<<"\n";
		//手动清理空间
		delete []arr; 
		delete []topArr;
	}
	cout<<"解决方案三的平均运行时间为:"<<sum/6<<"ms\n\n";
	
	cout<<"————————topK的解决方案四：使用优先队列priority_queue维护有序的数据序列————————\n";
	//初始化总运行时间
	sum = 0;
	for(int i=1;i<=6;i++){
		string filePath = basePath + to_string(i) + ".txt";
		int *arr=read_sample(filePath,size);
		// 获取程序开始时的时钟周期数
    	clock_t start = clock();
    	
    	//topK算法的解决方案四
		int *topArr = new int[15];
		priority_queue<int,vector<int>,greater<int>> pq;//建立小根堆
		for(int i=0;i<size;i++){
			if(i<10)
				pq.push(arr[i]);
			else
				if(arr[i]>pq.top()){
					pq.pop();
					pq.push(arr[i]);
				}
		}
		for(int i=9;i>=0;i--){
			topArr[i] = pq.top();
			pq.pop();
		}
		
		// 获取程序结束时的时钟周期数
    	clock_t end = clock();
    	// 计算程序运行时间（单位：毫秒）
    	double duration = double(end - start)* 1000 / CLOCKS_PER_SEC ;
    	sum += duration;
		cout<<"第"+to_string(i)+"组样本："<<duration<<"ms "
		<<(checkTopK(arr,size,topArr)?"true":"false")<<"\n";
		//手动清理空间
		delete []arr; 
		delete []topArr;
	}
	cout<<"解决方案四的平均运行时间为:"<<sum/6<<"ms\n\n";
	
	return 0;
}