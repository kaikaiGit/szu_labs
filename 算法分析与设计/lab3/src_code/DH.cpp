//最大度优先
#include "readSample.cpp"
using namespace std;

int max_vNum,eNum;
int matrix[1000][1000];
int ans = 0;
int color[1000];
int cNum = 4;

struct Vertex{
    int degree=0;
    int pos;
}vertex[1000];

void setVertex(){
	for(int i=1;i<=max_vNum;i++){
        vertex[i].pos=i;
        for(int j=1;j<=max_vNum;j++){
            vertex[i].degree += matrix[i][j];
        }
    }
}

bool cmp(Vertex v1,Vertex v2){
	return v1.degree > v2.degree;
}

bool check(int index){
	for(int i=1;i<=max_vNum;i++){
		//判断相邻点是否重色
		if(matrix[index][i] && color[index]==color[i])
			return false;
	}
	return true;
}

/* 要求一 */
/*void DH_dfs(int index){
	if(index > max_vNum){
		ans++;
		for(int i=1;i<=max_vNum;i++){
			cout<<color[i]<<" ";
		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){
		color[vertex[index].pos] = i;//涂色
		if(check(vertex[index].pos))DH_dfs(index+1);
		color[vertex[index].pos] = 0;//回溯
	}
}*/

/* 要求2 */
void DH_dfs(int index){
	if(ans >= 1e6)return;
	if(index > max_vNum){
		ans++;
//		for(int i=1;i<=max_vNum;i++){
//			cout<<color[i]<<" ";
//		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){
		color[vertex[index].pos] = i;//涂色
		if(check(vertex[index].pos))DH_dfs(index+1);
		color[vertex[index].pos] = 0;//回溯
	}
}

int main(){
	/* 要求一 */
	/*string filePath = "./map/test.txt"; //测试样本
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	
	setVertex();//初始化顶点集
	sort(vertex+1,vertex+max_vNum+1,cmp);//按节点的度降序排序
	DH_dfs(1);
	
	cout<<"一共有 "<<ans<<" 种涂色方案";*/
	
	/*要求2*/
	/*string filePath = "./map/given_map/le450_5a.col"; //测试样本
	cNum = 5;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	setVertex();//初始化顶点集
	sort(vertex+1,vertex+max_vNum+1,cmp);//按节点的度降序排序
	DH_dfs(1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_5a.col，" << "the time consumed is " << consume.count() << " ms.\n";
    
    string filePath = "./map/given_map/le450_15b.col"; //测试样本
	cNum = 15;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	setVertex();//初始化顶点集
	sort(vertex+1,vertex+max_vNum+1,cmp);//按节点的度降序排序
	DH_dfs(1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_15b.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    string filePath = "./map/given_map/le450_25a.col"; //测试样本
	cNum = 25;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	setVertex();//初始化顶点集
	sort(vertex+1,vertex+max_vNum+1,cmp);//按节点的度降序排序
	DH_dfs(1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_25a.col，" << "the time consumed is " << consume.count() << " ms.\n";
}
