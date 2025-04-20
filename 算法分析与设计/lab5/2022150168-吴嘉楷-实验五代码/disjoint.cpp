/*并查集优化*/
#pragma GCC optimize(3)
#include<iostream>
#include <chrono>
#include"readGraph.cpp"

//查找代表节点
int disjoint_find(int v){
	while(father[v] != v){
		father[v] = father[ father[v] ];
		v = father[v];
	}
	return v;
}

int count(){
	int cnt = 0;//连通分量数目最大值
	//初始化并查集
	for(int i=1;i<=vNum;i++){
		father[i] = i;
	}
	for(pair<int,int> p:edge){
		//检查两个顶点是否属于同个集合，不是则修改连通分量数目
		int set1 = disjoint_find(p.first);
		int set2 = disjoint_find(p.second);
		if(set1 != set2){
			father[set1] = set2; //合并两个集合
		}
	}
	for(int i=1;i<=vNum;i++){
		if(father[i]==i)
			cnt++;
	}
    return cnt;
}

int disjoint(){
	int bridge = 0;
	int cnt1 = count();//并查集计算原连通分量的数量
	//初始化并查集数组
	for(pair<int,int> p0:edge){
		int cnt2 = vNum;//连通分量数目最大值
		//初始化并查集
		for(int i=1;i<=vNum;i++){
			father[i] = i;
		}
		for(pair<int,int> p:edge){
			if(p0 == p)continue;//不加入这条边
			//检查两个顶点是否属于同个集合，不是则修改连通分量数目
			int set1 = disjoint_find(p.first);
			int set2 = disjoint_find(p.second);
			if(set1 != set2){
				father[set1] = set2; //合并两个集合
				cnt2--;
			}
		}
		if(cnt2 > cnt1){
			cout<<"edge between "<<p0.first<<" and "<<p0.second<<" is a bridge.\n";
			bridge++;
		}
	}
	return bridge;
}

int main(){
	cout<<"对于 基准+并查集 算法:\n";
//	string path = "./graphs/checkG.txt";
	string path = "./graphs/mediumDG.txt";
//	string path = "./graphs/largeG.txt";
	init(path);
	auto start = chrono::high_resolution_clock::now();
	int bridge = disjoint();
	auto end = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout<<"The graph totally has "<<bridge<<" bridges.\n";
	cout<<"The totally time_cost is "<<duration.count()/1000.0<<" ms\n";
	return 0;
}