//选择排序算法(升序）

//arr为数组名，len为数组长度
void select_sort(int *arr,int len){
	for(int i=0;i<len-1;i++){ //第i+1趟排序
		int minPos = i;
		for(int j=i+1;j<len;j++){
			if(arr[j]<arr[minPos])
				minPos = j;
		}
		swap(arr[i],arr[minPos]);
	}
}
