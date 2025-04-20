//向前探查一步
#include "readSample.cpp"
using namespace std;

int max_vNum,eNum;
int matrix[1000][1000];
int ans = 0;
int color[1000];
int cNum = 4;

struct Vertex{
	//邻接点是否存在该颜色，大于等于1为存在，小于1为不存在
    int colorAccess[25+1]; 
    int remainCNum;
    Vertex() {
		remainCNum = cNum; //默认初始化为全部颜色都可选
	}
}vertex[1000];

bool check(int index){
	for(int i=1;i<=max_vNum;i++){
		//判断相邻点是否重色
		if(matrix[index][i] && color[index]==color[i])
			return false;
	}
	return true;
}

void FC_Recover(const int pos,vector<int>&FCRecover){
    for(int it:FCRecover){
        vertex[it].colorAccess[color[pos]]= 0;
        vertex[it].remainCNum++;
    }
}

int FC(const int pos,vector<int>&FCRecover)
{   
	for(int j=1;j<=max_vNum;j++){//修改邻接点的colorAccess、remainCNum
		if(matrix[pos][j] && vertex[j].colorAccess[color[pos]]<1){
        	FCRecover.push_back(j);
			vertex[j].colorAccess[color[pos]] = pos;
			vertex[j].remainCNum--;
		}
	}
    for(int i=1;i<=max_vNum;i++)//查找邻近区域是否存在可涂颜色为0且未涂色的情况,若有,返回false
    {     
		if(vertex[i].remainCNum == 0 && !color[i]){
			return false;
		}
    }
    return true;
}

/* 要求一 */
/*void FS_dfs(int index){
	if(index > max_vNum){
		ans++;
		for(int i=1;i<=max_vNum;i++){
			cout<<color[i]<<" ";
		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){ //每种颜色都进行尝试
		//修改状态
		color[index] = i; 
		vector<int>FCRecover;
		if(check(index) && FC(index,FCRecover)){
			FS_dfs(index+1);//进入下一层
		}
		//状态恢复
		FC_Recover(index,FCRecover);
		color[index] = 0;
	}
}*/

/*要求2*/
void FS_dfs(int index){
	if(ans>=1)return;
	if(index > max_vNum){
		ans++;
//		for(int i=1;i<=max_vNum;i++){
//			cout<<color[i]<<" ";
//		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){ //每种颜色都进行尝试
		//修改状态
		color[index] = i; 
		vector<int>FCRecover;
		if(check(index) && FC(index,FCRecover)){
			FS_dfs(index+1);//进入下一层
		}
		//状态恢复
		FC_Recover(index,FCRecover);
		color[index] = 0;
	}
}

int main(){
	/* 要求一 */
	/*string filePath = "./map/test.txt"; //测试样本
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	FS_dfs(1);
	cout<<"一共有 "<<ans<<" 种涂色方案";*/
	
	/*要求2*/
	/*string filePath = "./map/given_map/le450_5a.col"; //测试样本
	cNum = 5;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	FS_dfs(1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_5a.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    /*string filePath = "./map/given_map/le450_15b.col"; //测试样本
	cNum = 15;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	FS_dfs(1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_15b.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    /*string filePath = "./map/given_map/le450_25a.col"; //测试样本
	cNum = 25;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	FS_dfs(1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_25a.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
}