//Ford-Fulkerson算法
#include "flowNetwork.cpp"
#include <string>
using namespace std;

bool dfs(int u, int &pathFlow) {
    if (u == t) return true;
    visit[u] = 1;

    for (int i = 0; i < edge[u].size(); i++) {
        EDGE &e = edge[u][i];
        if (!visit[e.for_point] && e.capacity > 0) {
            int minFlow = min(pathFlow, e.capacity);
            if (dfs(e.for_point, minFlow)) {
                e.capacity -= minFlow;
                edge[e.for_point][e.index].capacity += minFlow;
                pathFlow = minFlow;
                return true;
            }
        }
    }
    return false;
}

int Ford_Fulkerson()
{
    int maxFlow = 0;
    while (true) // 寻找增广路径
    {
        memset(visit, 0, sizeof(visit));
        int pathFlow = INF;
        if ( !dfs(s,pathFlow) )
            break;
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
	int maxFlow = Ford_Fulkerson();
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