#include "quick_sort.cpp"	//引入快速排序
//检验topK算法是否正确（必要但不充分条件）
bool checkTopK(int *arr,int len,int *topArr){ //topArr是从大到小排列的10个容量的数组
	//由于排序算法已被检验为正确，于是可以利用排序后的K个最大数来校验
	quick_sort(arr,0,len-1);
	for(int i=0;i<10;i++){
		if(arr[len-1-i]!=topArr[i])
			return false;
	}
	return true;
}
