//最少可选颜色优先
#include "readSample.cpp"
using namespace std;

int max_vNum,eNum;
int matrix[1000][1000];
int ans = 0;
int color[1000];
int cNum = 4;

struct Vertex{
    bool colorAccess[25+1];
    int remainCNum = 0;
}vertex[1000];

bool check(int index,int color_kind){
	for(int i=1;i<=max_vNum;i++){
		//判断相邻点是否重色
		if(matrix[index][i] && color[i] == color_kind)
			return false;
	}
	return true;
}

int MRV_find()
{   
    int minC = cNum;
    int pos=0;
    for(int i=1;i<=max_vNum;i++)//找出可涂颜色数最少且没涂过颜色的点,返回下标
    {     
    	vertex[i].remainCNum = 0;
        for(int j=1;j<=cNum;j++){
        	if(!vertex[i].colorAccess[j])
        		vertex[i].remainCNum++;
		}
		if(minC > vertex[i].remainCNum && !color[i]){
			minC = vertex[i].remainCNum;
			pos = i;
		}
    }
    return pos;
}

/* 要求一 */
/*void MRV_dfs(int index,int pos){
	if(index > max_vNum){
		ans++;
		for(int i=1;i<=max_vNum;i++){
			cout<<color[i]<<" ";
		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){ //每种颜色都进行尝试
		if(check(pos,i)){
			//修改状态
			color[pos] = i;         
			vector<int>MRVRecover;
			for(int j=1;j<=max_vNum;j++){//修改邻接点的colorAccess
				if(matrix[pos][j] && !vertex[j].colorAccess[i]){
                	MRVRecover.push_back(j);
					vertex[j].colorAccess[i] = true;
				}
			}
			int coloring_pos = 	MRV_find();//找到涂色点的位置
			//找不到可涂色的点,直接回溯
			if(coloring_pos==0 && index != max_vNum)return;
			//否则继续
			MRV_dfs(index+1,coloring_pos);//进入下一层
			//状态恢复
			color[pos] = 0;	
			for(int v : MRVRecover){
				vertex[v].colorAccess[i] = false;
			}
		}
	}
}*/

/*要求2*/
void MRV_dfs(int index,int pos){
	if(ans >= 1e6)return;
	if(index > max_vNum){
		ans++;
//		for(int i=1;i<=max_vNum;i++){
//			cout<<color[i]<<" ";
//		}cout<<"\n";
		return;
	}
	for(int i=1;i<=cNum;i++){ //每种颜色都进行尝试
		if(check(pos,i)){
			//修改状态
			color[pos] = i;         
			vector<int>MRVRecover;
			for(int j=1;j<=max_vNum;j++){//修改邻接点的colorAccess
				if(matrix[pos][j] && !vertex[j].colorAccess[i]){
                	MRVRecover.push_back(j);
					vertex[j].colorAccess[i] = true;
				}
			}
			int coloring_pos = 	MRV_find();//找到涂色点的位置
			//找不到可涂色的点,直接回溯
			if(coloring_pos==0 && index != max_vNum)return;
			//否则继续
			MRV_dfs(index+1,coloring_pos);//进入下一层
			//状态恢复
			color[pos] = 0;	
			for(int v : MRVRecover){
				vertex[v].colorAccess[i] = false;
			}
		}
	}
}
int main(){
	/* 要求一 */
	/*string filePath = "./map/test.txt"; //测试样本
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	MRV_dfs(1,1);
	cout<<"一共有 "<<ans<<" 种涂色方案";*/
	
	/*要求2*/
	string filePath = "./map/given_map/le450_5a.col"; //测试样本
	cNum = 5;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	MRV_dfs(1,1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_5a.col，" << "the time consumed is " << consume.count() << " ms.\n";
    
    /*string filePath = "./map/given_map/le450_15b.col"; //测试样本
	cNum = 15;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	MRV_dfs(1,1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_15b.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    /*string filePath = "./map/given_map/le450_25a.col"; //测试样本
	cNum = 25;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
    auto start = chrono::high_resolution_clock::now();
	MRV_dfs(1,1);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_25a.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
}