//快速排序算法(升序）

// 分割函数，将数组分成左右两部分，并返回基准元素的索引位置
int partition(int *arr,int low,int high){
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

//arr为数组名，low为待排序序列的起始下标，high为待排序序列结尾元素下标
void quick_sort(int *arr,int low,int high){
	if(low < high){
		int pivotIdx = partition(arr,low,high);//获取基准数的下标
		quick_sort(arr,low,pivotIdx-1); //对左子数组进行排序
		quick_sort(arr,pivotIdx+1,high); //对右子数组进行排序
	}
}
