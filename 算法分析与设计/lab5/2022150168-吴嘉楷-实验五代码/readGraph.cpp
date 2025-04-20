/*读取图数据，初始化邻接表*/
#include<fstream>
#include<forward_list>
#include<vector>
//#include <unordered_set>
using namespace std;

const int vMax = 1e6;
int vNum,eNum;
forward_list<int> graph[vMax+5];//邻接表
vector< pair<int,int> > edge;	//边集
int father[vMax+5];				//并查集代表元数组 or 并查集生成树
int bridgeTag[vMax+5];			//点代边数组记录遍历过的环边(0:不是桥）
int depth[vMax+5];				//各节点在其生成树中的深度
bool visit[vMax+5];				//顶点访问情况

void init(string filePath){
	//清空邻接表数据
	for(int i=1;i<=vMax;i++){
		graph[i].clear();
	}
	//读取图的数据
	ifstream file;
    file.open(filePath);
    if(!file.is_open())cout<<"Error!"<<endl;
    file>>vNum>>eNum;
    int a,b;
    while(file>>a>>b){
    	if(a==b)continue; //去除自环边
    	graph[a].push_front(b);
    	graph[b].push_front(a);
    	edge.push_back({a,b});
	}
//	unordered_set<pair<int,int>> unique_set(edge.begin(), edge.end());
}