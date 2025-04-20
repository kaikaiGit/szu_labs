//最少可选颜色优先 + 最大度优先 + 向前探测一步 + 颜色轮换
#include "readSample.cpp"
using namespace std;

int max_vNum,eNum;
int matrix[1000][1000];
long long ans = 0;
int color[1000];
int cNum = 4;

clock_t startTime, endTime;//毫秒级程序计时

struct Vertex{
    bool colorAccess[25+1];
    int remainCNum;
    int degree;
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

bool check(int index,int color_kind){
	for(int i=1;i<=max_vNum;i++){
		//判断相邻点是否重色
		if(matrix[index][i] && color[i] == color_kind)
			return false;
	}
	return true;
}

int MRV_DH_find()
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
		if(vertex[i].remainCNum == 0 && !color[i])return 0;
		if(color[i])continue;
		if(minC > vertex[i].remainCNum){
			minC = vertex[i].remainCNum;
			pos = i;
		}
		else if(minC == vertex[i].remainCNum){
			if(vertex[i].degree > vertex[pos].degree){
				pos = i;
			}
		}
    }
    return pos;
}

/*要求2*/
int MRV_DH_FS_rotate(int index,int pos,int usedColor){
	if(ans >= 1e6)
		return 0;
		
	if(index == max_vNum){
		ans += vertex[pos].remainCNum;
		return vertex[pos].remainCNum;
	}
	int s = 0;
	for(int i=1;i<=cNum;i++){ //每种颜色都进行尝试
		if(vertex[pos].colorAccess[i])continue;
		int ss = 0;
		if(check(pos,i)){
			//修改状态 
			color[pos] = i; 
			vector<int>MRVRecover;
			for(int j=1;j<=max_vNum;j++){//修改邻接点的状态
				if(matrix[pos][j] && !vertex[j].colorAccess[i]){
                	MRVRecover.push_back(j);
					vertex[j].colorAccess[i] = true;
				}
			}
			int coloring_pos = 	MRV_DH_find();//找到涂色点的位置
			//找不到可涂色的点 或 下一个点不可涂色,直接回溯
			if(coloring_pos==0 && index != max_vNum){
				//状态恢复
				color[pos] = 0; 
				for(int v : MRVRecover){
					vertex[v].colorAccess[i] = false;
				}
				return 0;
			}
			//否则继续
			bool isNewColor = i > usedColor;//是否为新颜色
			if(isNewColor)
				ss = MRV_DH_FS_rotate(index+1,coloring_pos,usedColor+1);//进入下一层,使用了新颜色
			else
				ss = MRV_DH_FS_rotate(index+1,coloring_pos,usedColor);//进入下一层，未使用新颜色
			
			if(ans >= 1e6)return 0;
			//状态恢复
			for(int v : MRVRecover){
				vertex[v].colorAccess[i] = false;
			}
			color[pos] = 0;	
			
			//关键剪枝
			if (isNewColor) {
				s += ss * (cNum - usedColor);
				ans += ss * (cNum - usedColor - 1);
				break;
			}
			s += ss;
			
		}
	}
	return s;
}
int main(){
	/* 要求一 */
	/*string filePath = "./map/test.txt"; //测试样本
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	setVertex();
    auto start = chrono::high_resolution_clock::now();
	MRV_DH_FS_rotate(1,1,0);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_5a.col，" << "the time consumed is " << consume.count() << " ms.\n";
	cout<<"一共有 "<<ans<<" 种涂色方案";*/
	
	/*要求2*/
	/*string filePath = "./map/given_map/le450_5a.col"; //测试样本
	cNum = 5;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	setVertex();
    auto start = chrono::high_resolution_clock::now();
	MRV_DH_FS_rotate(1,1,0);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_5a.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    /*string filePath = "./map/given_map/le450_15b.col"; //测试样本
	cNum = 15;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	setVertex();
    auto start = chrono::high_resolution_clock::now();
	MRV_DH_FS_rotate(1,43,0);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_15b.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    /*string filePath = "./map/given_map/le450_25a.col"; //测试样本
	cNum = 25;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	setVertex();
    auto start = chrono::high_resolution_clock::now();
	MRV_DH_FS_rotate(1,1,0);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For le450_25a.col，" << "the time consumed is " << consume.count() << " ms.\n";*/
    
    /*要求3*/
    string filePath = "./map/mymap/30p_90e_4a.txt"; //测试样本
	cNum = 4;
	read(filePath,max_vNum,eNum,matrix); //读取样本,构造matrix
	setVertex();
    auto start = chrono::high_resolution_clock::now();
	MRV_DH_FS_rotate(1,1,0);
	auto end = chrono::high_resolution_clock::now();
    auto consume = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "For 30p_120e_4a，we found " << ans << " 个解。the time consumed is " << consume.count() << " ms.\n";
}