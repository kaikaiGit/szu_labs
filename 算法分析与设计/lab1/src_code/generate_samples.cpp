//包含生成n个随机数函数的文件
#include<cstdlib> //包含rand()函数
#include<ctime> //包含time()函数
using namespace std;

//生成n个随机数样本
int* generate_random(int n){
	unsigned seed = time(0);
	srand(seed); //提供随时数种子
	int *arr = new int[n+5];
	for(int i=0;i<n;i++){
		arr[i]=rand();
	}
	return arr;
}
