// 生成随机数
#include<iostream>
#include<ctime>
#include<fstream>
#include<algorithm>
#include<string>
using namespace std;

struct Edge{
	int a;
	int b;
}edge[10000];
int map[1000][1000];//邻接矩阵

void makeSample(int eNum,int max_vNum){
	srand(time(0));
    int x,y,cnt=0;
    while(cnt < eNum){
    	x = rand()%max_vNum + 1;
    	y = rand()%max_vNum + 1;
    	if(x>=y)continue; //还原地图特征
    	if(map[x][y])continue; //去重,保证有eNum条边
    	edge[cnt].a=x;edge[cnt].b=y;
        map[x][y] = map[y][x] = 1;
        cnt++;
	}
}

bool cmp(Edge e1,Edge e2)
{
    return e1.a<e2.a;
}

int main(){
	/*固定顶点个数*/
//	const int max_vNum=30;
//	
//	for(int eNum=30;eNum<=30;eNum+=30){
//		ofstream ofs;
//		string filename = "./map/mymap/"+to_string(max_vNum)+"p_"+to_string(eNum)+"e_4a.txt";
//	    ofs.open(filename,ios::out);
//	    makeSample(eNum,max_vNum);
//	    sort(edge,edge+eNum,cmp);
//	    ofs<<"p edge "<<max_vNum<<" "<<eNum<<"\n";
//	    for(int i=0;i<eNum;i++)
//	    {
//	        ofs<<"e "<<edge[i].a<<" "<<edge[i].b<<endl;
//	    }
//	    ofs.close();
//	}
	
	/*固定边的条数*/
	const int eNum=1000;
	
	for(int max_vNum=150;max_vNum<=350;max_vNum+=50){
		ofstream ofs;
		string filename = "./map/mymap/"+to_string(max_vNum)+"p_"+to_string(eNum)+"e_4a.txt";
	    ofs.open(filename,ios::out);
	    makeSample(eNum,max_vNum);
	    sort(edge,edge+eNum,cmp);
	    ofs<<"p edge "<<max_vNum<<" "<<eNum<<"\n";
	    for(int i=0;i<eNum;i++)
	    {
	        ofs<<"e "<<edge[i].a<<" "<<edge[i].b<<endl;
	    }
	    ofs.close();
	}
}