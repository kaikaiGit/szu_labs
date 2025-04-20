//Dinic算法
#include "flowNetwork.cpp"
#include <string>
#include <queue>
using namespace std;

int level[max_Num+5]; // 用于层次网络
int iter[max_Num+5];  // 当前弧优化

//BFS构建层次网络
bool bfs() {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const EDGE &e : edge[u]) {
            if (e.capacity > 0 && level[e.for_point] < 0) {
                level[e.for_point] = level[u] + 1;
                q.push(e.for_point);
            }
        }
    }
    return level[t] != -1;
}

//使用DFS分层增广
int dfs(int u, int flow) {
    if (u == t) return flow;

    for (int &i = iter[u]; i < edge[u].size(); i++) { // 避免重复
        EDGE &e = edge[u][i];

        if (e.capacity > 0 && level[u] < level[e.for_point]) {
            int pathFlow = dfs(e.for_point, min(flow, e.capacity));
            if (pathFlow > 0) {
                e.capacity -= pathFlow;
                edge[e.for_point][e.index].capacity += pathFlow;
                return pathFlow;
            }
        }
    }
    return 0;
}

int dinic() {
    int maxFlow = 0;
    while (bfs()) {
        memset(iter, 0, sizeof(iter));
        int flow;
        while ((flow = dfs(s, INF)) > 0) {
            maxFlow += flow;
        }
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
	int maxFlow = dinic();
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