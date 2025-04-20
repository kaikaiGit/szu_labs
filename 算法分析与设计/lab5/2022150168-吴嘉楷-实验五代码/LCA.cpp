/*并查集 + 生成树 + LCA*/
#pragma GCC optimize(3)
#include<iostream>
#include <chrono>
#include<queue>
#include"readGraph.cpp"

//dfs构建生成树
void dfs(int current, int d, int fa){
	depth[current] = d;	//保存深度
	father[current] = fa;	//扩大生成树
	for(auto v:graph[current]){
		if(visit[v])
			continue;
		visit[v] = true;
		bridgeTag[v] = 1;
		dfs(v, d+1, current); //往邻接节点dfs
	}
}
//bfs构建生成树
void bfs(int root){
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int current = q.front();
		q.pop();
		for(auto v:graph[current]){
			if(visit[v])
				continue;
			visit[v] = true;
			bridgeTag[v] = 1;
			depth[v] = depth[current]+1;	//保存深度
			father[v] = current;	//扩大生成树
			q.push(v);
		}
	}
}

//构建生成树森林
void create_tree(){
	/*dfs*/
//	for(int i=1;i<=vNum;i++){
//		if(!visit[i]){
//			visit[i] = true;
//			dfs(i, 0, i);
//		}
//	}
	/*bfs*/
	queue<int> q;
	for(int i=1;i<=vNum;i++){
		if(!visit[i]){
			visit[i] = true;
			father[i] = i;
			bfs(i);
		}
	}
}

void pathZip(int child, int ancestor){
	/*递归实现*/
//	if(father[child] == ancestor)
//		return;
//	int saveChild = child;
//	child = father[child];
//	father[saveChild] = ancestor;
//	pathZip(child,ancestor);

	/*循环实现*/
	while(father[child] != ancestor){
		int saveChild = child;
		child = father[child];
		father[saveChild] = ancestor;
	}
}

void LCA(int v1,int v2){
	if(father[v1] == v2 || father[v2] == v1)//当前边在生成树上
		return;
	int save_v1 = v1, save_v2 = v2;
	while(true){
		//左边深，v1先向上查找
		if(depth[v1] > depth[v2]){
			bridgeTag[v1] = 0;
			v1 = father[v1];
		}
		//右边深，v2先向上查找
		else if(depth[v1] < depth[v2]){
			bridgeTag[v2] = 0;
			v2 = father[v2];
		}
		else{
			if(v1 != v2){ //没找到公共祖先，同时向上查找
				bridgeTag[v1] = 0;
				v1 = father[v1];
				bridgeTag[v2] = 0;
				v2 = father[v2];
			}
			else
				break;
		}
	}
	//路径压缩
	if(save_v1!=v1)
		pathZip(save_v1,v1);
	if(save_v2!=v2)
		pathZip(save_v2,v2);
}

int disjoint_LCA(){
	int bridge = 0;
	//构造生成树森林
	create_tree();
	//遍历边集中的非生成树的边
	for(auto e:edge){
		LCA(e.first,e.second);
	}
	for(int i=1;i<=vNum;i++){
		if(bridgeTag[i]){
			cout<<"edge between "<<i<<" and "<<father[i]<<" is a bridge.\n";
			bridge++;
		}	
	}
	return bridge;
}

int main(){
	cout<<"对于 并查集+生成树+LCA 算法:\n";
//	string path = "./graphs/checkG.txt";
	string path = "./graphs/mediumDG.txt";
//	string path = "./graphs/largeG.txt";
	init(path);
	auto start = chrono::high_resolution_clock::now();
	int bridge = disjoint_LCA();
	auto end = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout<<"The graph totally has "<<bridge<<" bridges.\n";
	cout<<"The totally time_cost is "<<duration.count()/1000.0<<" ms\n";
	return 0;
}