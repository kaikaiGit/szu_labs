//合并排序算法(升序）

const int N = 1e6;
int save[N+5]; //辅助数组

void merge(int *arr,int low,int mid,int high){
	int i,j,k;
	//将arr中所有元素复制到save数组中
	for(k=low;k<=high;k++){
		save[k] = arr[k];
	}
	for(i=low,j=mid+1,k=low;i<=mid&&j<=high;k++){
		//将较小值依次添加到arr数组中（覆盖原元素）
		if(save[i]<=save[j])
			arr[k] = save[i++];
		else
			arr[k] = save[j++];
	}
	//处理未添加到arr中的元素
	while(i<=mid)arr[k++] = save[i++];
	while(j<=high)arr[k++] = save[j++];
}

//arr为数组名，low为待排序序列的起始下标，high为待排序序列结尾元素下标
void merge_sort(int *arr,int low,int high){
	if(low<high){
		int mid = (low+high)/2;
		merge_sort(arr,low,mid); //排左边
		merge_sort(arr,mid+1,high); //排右边
		merge(arr,low,mid,high);
	}
}
