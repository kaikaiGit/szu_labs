#include<bits/stdc++.h>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;
random_device rd;//随机数生成
mt19937 gen(rd());
const int accessNum = 2e8;

void access(int size)		//访问函数 
{
	double cost_time;
	int sum=0; 
	int n = size / sizeof(char);
	char* buf = new char[n];
	uniform_int_distribution<> big_rand(0, n-1);	//大规模随机数0-n-1 
	vector<int> random_num;		 
	memset(buf, 1, sizeof(char) * n);
	for(int i=0; i<accessNum; i++)	//随机产生数据压入数组,作为随机取数的位置 
	{
		random_num.push_back(big_rand(gen)); 
	}
	high_resolution_clock::time_point t1 = high_resolution_clock::now();//计时 
	for(int i=0; i<accessNum; i++)	
	{
		sum =sum+ buf[random_num[i]];	//取数 
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_temp;
	time_temp = duration_cast<duration<double>>(t2 - t1);
	cost_time = time_temp.count();
	
	cout<< "size=" << (size/1024) << "KB\t time=";
	cout<< cost_time << "s" << endl;
	delete[] buf;
}

void test_cache()
{
	vector<int> sizes{8,16,32,64,128,256,384,512,768,1024,1536,2048,3072,4096,5120,6144,7168,8192,10240,12288,16384};
	for(auto s : sizes)
	{
		access(s*1024);
	}
}

void test_line(char *cache,int line)
{
	double cost_time;
	int n = accessNum / sizeof(char);
	int sum = 0;
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	for (int j = 0; j < line; j++)
	{
		for (int i = 0; i < n; i = i+ line)
		{
			sum = sum+ cache[i];//取数 
		}
	}
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	duration<double> time_temp;
	time_temp = duration_cast<duration<double>>(t2 - t1);
	cost_time = time_temp.count();
	cout << "length=" << line << "B\t";
	cout << "time=" << cost_time << " s" << endl;
} 

int main()
{
	vector<int> line{ 1,2,4,8,16,32,64,96,128,192,256,512,1024,1536,2048 };
//	test_cache();
	char *cache = new char[accessNum / sizeof(char)];
	memset(cache, 1, accessNum);
	for(auto l : line)
	{
		test_line(cache, l);
	}
}
