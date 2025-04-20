//Edmond-Karp算法
#include "flowNetwork.cpp"
#include <string>
#include <queue>
using namespace std;

int parent[max_Num+5]; 		// 用于存储增广路径中的父节点
int minCapacity[max_Num+5]; // 用于存储增广路径中的最小容量

bool bfs() {
    memset(parent, -1, sizeof(parent));
    memset(minCapacity, 0, sizeof(minCapacity));
    queue<int> q;
    q.push(s);
    parent[s] = -2; // 表示源点已经被访问
    minCapacity[s] = INF; // 源点的初始容量设为无穷大
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < edge[u].size(); i++) {
            EDGE &e = edge[u][i];
            //若未访问过 且 边容量>0
            if (parent[e.for_point] == -1 && e.capacity > 0) {
                parent[e.for_point] = u;
                minCapacity[e.for_point] = min(minCapacity[u], e.capacity);
                if (e.for_point == t) return true;
                q.push(e.for_point);
            }
        }
    }
    return false;
}

int Edmond_Karp() {
    int maxFlow = 0;
    while ( bfs() ) { //找到一条增广路径则依靠parent数组更新流网络的容量
        int pathFlow = minCapacity[t]; // 增广路径上的最小容量
        // 不断查找前驱节点，更新残余网络中的容量
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            for (EDGE &e : edge[u]) {
                if (e.for_point == v) {
                    e.capacity -= pathFlow;
                    edge[v][e.index].capacity += pathFlow;
                    break;
                }
            }
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

// 球队x是否会被淘汰
bool isEliminate(int x){
	//计算源点流出的极限流量
	int flowFromS = 0;
    for (int i = 0; i < n; i++) {
        if (i == x) continue;
        for (int j = i + 1; j < n; j++) {
            if (j == x) continue;
            flowFromS += g[i][j];
        }
    }
	//计算最大流
	int maxFlow = Edmond_Karp();
    return flowFromS > maxFlow;
}

int main(){
	/*测试样本*/
//	for(int x = 0; x < n; x++){
//		//平凡淘汰
//		if( !createFlowNetwork(x) )continue;
//		//非平凡淘汰
//		if( isEliminate(x))continue;
//		cout<<"“"<<teams[x]<<"” may win the champion !\n";
//	}
	/*随机样本*/
	for(int i=500;i<=3000;i+=500){
		string filename = "./samples/teamNum_"+to_string(i);
		//读取样本数据
		read_sample(filename,i);
		cout<<"对于球队数为"<<i<<"的情况：\n";
		// 记录起始时间
        auto start = chrono::high_resolution_clock::now();
		for(int x = 0; x < i; x++){
			//平凡淘汰
			if( !createFlowNetwork(x) )continue;
			//非平凡淘汰
			if( isEliminate(x))continue;
//			cout<<"“球队"<<x<<"” may win the champion !\n";
		}
		// 记录结束时间
        auto end = chrono::high_resolution_clock::now();
        // 计算执行时间
        chrono::duration<double, milli> duration = end - start;
        cout<<"算法耗时为："<<duration.count()<<"ms \n";
	}
	return 0;
}