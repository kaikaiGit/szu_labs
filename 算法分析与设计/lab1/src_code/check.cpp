//检验升序排序是否完成（必要但不充分条件）
bool check(int *arr,int len){
	for(int i=0;i<len-1;i++){
		if(arr[i+1]<arr[i])
			return false;
	}
	return true;
}