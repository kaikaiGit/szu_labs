//preflowPush算法
#include "flowNetwork.cpp"
#include <string>
#include <climits>
#include <queue>
using namespace std;

vector<int> height, excess, count;

void bfsHeightInit(int n, int t) {
    fill(height.begin(), height.end(), n);
    queue<int> q;
    height[t] = 0;
    q.push(t);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (EDGE& e : edge[u]) {
            int v = e.for_point;
            if (height[v] == n && edge[v][e.index].capacity - edge[v][e.index].flow > 0) {
                height[v] = height[u] + 1;
                q.push(v);
            }
        }
    }
}

//推流
void push(int u, int e_idx) {
    EDGE& e = edge[u][e_idx];
    int v = e.for_point;
    int delta = min(excess[u], e.capacity - e.flow);
    e.flow += delta;
    edge[v][e.index].flow -= delta;
    excess[u] -= delta;
    excess[v] += delta;
}

//重新标记
void relabel(int u, int n) {
    int minHeight = INT_MAX;
    for (EDGE& e : edge[u]) {
        if (e.capacity > e.flow) {
            minHeight = min(minHeight, height[e.for_point]);
            height[u] = minHeight + 1;
        }
    }
}

//排空
void discharge(int u, int n) {
    while (excess[u] > 0) {
        bool pushed = false;
        for (int i = 0; i < edge[u].size() && excess[u] > 0; i++) {
            EDGE& e = edge[u][i];
            if (e.capacity > e.flow && height[u] == height[e.for_point] + 1) {
                push(u, i);
                pushed = true;
            }
        }
        if (!pushed) {
            relabel(u, n);
            count[height[u]]++;
        }
    }
}

void gapRelabel(int n, int height_value) {
    for (int i = 0; i < n; i++) {
        if (height[i] > height_value) {
            height[i] = n + 1;
        }
    }
}

//预流推进算法
int preflowPush(int s, int t,int n) {
    height.resize(n, 0);
    excess.resize(n, 0);
    count.resize(2 * n, 0);

    bfsHeightInit(n, t);

    for (EDGE& e : edge[s]) {
        excess[e.for_point] += e.capacity;
        edge[e.for_point][e.index].flow -= e.capacity;
        e.flow = e.capacity;
    }

    priority_queue<pair<int, int>> pq;  // max-heap
    for (int i = 0; i < n; i++) {
        if (i != s && i != t && excess[i] > 0) {
            pq.push({height[i], i});
        }
    }

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        int old_height = height[u];
        discharge(u, n);
        if (height[u] != old_height) {
            pq.push({height[u], u});
        }

        if (count[old_height] == 0) {
            gapRelabel(n, old_height);
        }
    }

    return excess[t];
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
	int maxFlow = preflowPush(s, t, t + 1);
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