//插入排序算法(升序）

//arr为数组名，len为数组长度
void insert_sort(int *arr,int len){
	//遍历未排序部分
	for(int i=1;i<len;i++){
		int num = arr[i];
		int j=i-1;
		for(;j>=0&&arr[j]>num;j--){
			arr[j+1] = arr[j]; //元素后移一位
		}
		arr[j+1] = num; //插入
	}
}
