//冒泡排序算法(升序）

//arr为数组名，len为数组长度
void bubble_sort(int *arr,int len){
	for(int i=1;i<len;i++){ //第i趟排序
		bool flag = true;
		for(int j=0;j<len-i;j++){ //下标为j的数
			if(arr[j]>arr[j+1]){
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
				flag = false;
			}
		}
		if(flag)break;
	}
}
