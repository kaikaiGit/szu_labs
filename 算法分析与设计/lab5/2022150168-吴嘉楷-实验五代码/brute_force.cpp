/*基准算法*/
//#pragma GCC optimize(3)
#include<iostream>
#include <chrono>
#include<queue>
#include"readGraph.cpp"

void dfs(int index){
	visit[index] = true;   //表示已访问
    //遍历该点的邻接表
    for(int v : graph[index]){
    	if(visit[v])continue;
    	dfs(v);
	}
}
void bfs(int root){
	queue<int> q;
	q.push(root);
	while(!q.empty()){
		int index = q.front();
		q.pop();
		visit[index] = true;
		//遍历该点的邻接表
	    for(int v : graph[index]){
	    	if(visit[v])continue;
	    	q.push(v);
		}
	}
}

int count(){
	int cnt=0;
    for(int i=1;i<=vNum;i++)
        visit[i] = false;
    //遍历每个点,若未访问则调用dfs
    for(int i=1;i<=vNum;i++)
    {
        if(!visit[i])
        {
            bfs(i);
            cnt++;
        }
    }
    return cnt;
}

int bruteForce(){
	int bridge = 0;
	int cnt1 = count();//计算连通分量的数量
	for(pair<int,int> p:edge){
		//移除一条边
		int a = p.first, b = p.second;
		graph[a].remove(b);
		graph[b].remove(a);
		int cnt2 = count();//计算连通分量的数量
		if(cnt2>cnt1){
			cout<<"edge between "<<a<<" and "<<b<<" is a bridge.\n";
			bridge++;
		}
		//恢复边
		graph[a].push_front(b);
		graph[b].push_front(a);
	}
	return bridge;
}

int main(){
	cout<<"对于基准算法：\n";
//	string path = "./graphs/checkG.txt";
//	string path = "./graphs/mediumDG.txt";
	string path = "./graphs/largeG.txt";
	init(path);
	auto start = chrono::high_resolution_clock::now();
	int bridge = bruteForce();
	auto end = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	cout<<"The graph totally has "<<bridge<<" bridges.\n";
	cout<<"The totally time_cost is "<<duration.count()/1000.0<<" ms\n";
	return 0;
}