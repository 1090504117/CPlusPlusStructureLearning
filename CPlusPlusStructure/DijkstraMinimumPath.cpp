#include "Utils.h"
#include "DijkstraMinimumPath.h"

int DijkstraMinimumPath(vector<vector<int>>& triangle)
{
	int size = (int)triangle.size();
	if (size < 1) return 0;
	if (1 == size) return triangle[0][0];
	int calNum = 0;
	int temp, num;
	vector<int> a;
	a.push_back(triangle[0][0]);
	for (int i = 1; i < size; i++)
	{
		vector<int> &tempVector = triangle[i];
		a.push_back(tempVector[i]);
		temp = a[0];
		for (int j = 1; j < i; j++)
		{
			num = a[j];
			calNum = temp < num ? temp + tempVector[j] : num + tempVector[j];
			temp = num;
			a[j] = calNum;
		}
		a[0] = tempVector[0] + a[0];
		a[i] = tempVector[i] + temp;
	}
	int min = a[0];
	for (int i = 0; i < size; i++)
	{
		if (a[i] < min) min = a[i];
	}
	return min;
}

int DijkstraMinimumPath2(vector<vector<int>>& triangle)
{
	int size = (int)triangle.size();
	if (size < 1) return 0;
	vector<int> a(triangle.back());
	for (int i = size - 2; i > -1; i--)
	{
		for (int j = 0; j <= i; j++)	//此处层出现问题 j <=i ,原先可能是j < i,故严格注意边界问题
		{
			a[j] = triangle[i][j] + MinInt(a[j + 1], a[j]);
		}
	}
	return a[0];
}

void DijkstraMinimumPathTest()
{
	vector<vector<int>> testVector;
	int a[] =
	{
		2,
		3,4,
		6,5,7,
		4,1,8,3
	};
	int len = 4;
	int index = 0;
	for (int i = 0; i < len; i++)
	{
		vector<int> tmpVector;
		for (int j = 0; j <= i; j++)
			tmpVector.push_back(a[index++]);
		testVector.push_back(tmpVector);
	}
	printf("min = %d", DijkstraMinimumPath2(testVector));
}

/*
//百度给的这个算法不是很好懂，需要改成自己这一套

void dijkstra(const int &beg,//出发点
	const vector<vector<int> > &adjmap,//邻接矩阵，通过传引用避免拷贝
	vector<int> &dist,//出发点到各点的最短路径长度
	vector<int> &path)//路径上到达该点的前一个点
					  //负边被认作不联通
					  //福利：这个函数没有用任何全局量，可以直接复制！
{
	const int &NODE = adjmap.size();//用邻接矩阵的大小传递顶点个数，减少参数传递
	dist.assign(NODE, -1);//初始化距离为未知
	path.assign(NODE, -1);//初始化路径为未知
	vector<bool> flag(NODE, 0);//标志数组，判断是否处理过
	dist[beg] = 0;//出发点到自身路径长度为0
	while (1)
	{
		int v = -1;//初始化为未知

				//*start---------------------- 这一块就是处理优先队列。。。 
						//搞得好复杂，
						//搜寻目前剩下的候选子节点中距离最小的点，进行广播，
						//这个for循环着实写的恶心。以为每次都会遍历，其实不然
		for (int i = 0; i != NODE; ++i)
			if (!flag[i] && dist[i] >= 0)			//寻找未被处理过且
				if (v<0 || dist[i]<dist[v])			//距离最小的点 这样写是因为
					v = i;					

				//---------------------------end*

		if (v<0)return;//所有联通的点都被处理过
		flag[v] = 1;//标记
		for (int i = 0; i != NODE; ++i)	
			if (adjmap[v][i] >= 0)//有联通路径且
				if (dist[i]<0 || dist[v] + adjmap[v][i]<dist[i])//不满足三角不等式
				{
					dist[i] = dist[v] + adjmap[v][i];//更新
					path[i] = v;//记录路径
				}
	}
}





int main()
{
	int n_num, e_num, beg;//含义见下
	cout << "输入点数、边数、出发点：";
	cin >> n_num >> e_num >> beg;
	vector<vector<int> > adjmap(n_num, vector<int>(n_num, -1));//默认初始化邻接矩阵
	for (int i = 0, p, q; i != e_num; ++i)
	{
		cout << "输入第" << i + 1 << "条边的起点、终点、长度（负值代表不联通）：";
		cin >> p >> q;
		cin >> adjmap[p][q];
	}
	vector<int> dist, path;//用于接收最短路径长度及路径各点
	dijkstra(beg, adjmap, dist, path);
	for (int i = 0; i != n_num; ++i)
	{
		cout << beg << "到" << i << "的最短距离为" << dist[i] << "，反向打印路径：";
		for (int w = i; path[w] >= 0; w = path[w])
			cout << w << "<-";
		cout << beg << '\n';
	}
}
*/

/*
//--------------------------------------------------------------------------------------------
//别问我为什么用longlong 这是洛谷的单源最短路的模板
const long long INF = 2147483647;
const int MAXN = 10000;
const int MAXM = 500000;
int n, m, s;//n个点 m条边 从第s号点开始
int node;//当前正在处理的节点
long long minn;
long long dist[MAXN];//每个点到起点的距离
bool vis[MAXN];//是否处理过
struct Edge {//边的结构体 
	int w;//边权
	int pre, to;//pre是出发点 to是终点 这个是有向边
}l[MAXM];
struct Node {//节点的结构体
	int num;//以这个点为起点的边的个数
	vector<int> about;//利用stl存以这个点为起点的边的编号，不知道的就把ta当成动态数组吧
}a[MAXN];
int find_new()//每次处理完找新节点的函数
{
	for (int i = 1; i <= n; i++)//找新的开始点 
	{
		if (vis[i] == 0 && minn>dist[i])//从没有处理过的点里找离起点最近的进行处理
		{
			minn = dist[i];//贪心找最小
			node = i;//node其实就是下一步要被处理的点的编号
		}
	}
}
long long min_(long long x, long long y)//手写min函数更快~
{
	return x>y ? x : y;
}
int main()
{
	cin >> n >> m >> s;
	for (int i = 1; i <= n; i++)
	{
		dist[i] = INF;//初始化 所有点到起点的距离设成无限大
					  //      cout<<dist[i]<<endl;//DEBUG
	}
	int x, y, z;
	for (int i = 1; i <= m; i++)//输入边
	{
		scanf("%d%d%d", &x, &y, &z);//依次是 起点 终点 边权
		l[i].pre = x, l[i].to = y;
		l[i].w = z;
		a[x].num++;//起点的出度+1
		a[x].about.push_back(i);//记录这个边
	}
	dist[s] = 0;//起点距离设成0
	node = s;//从起点开始处理
	while (!vis[node])
	{
		vis[node] = 1;//已经处理过了
		minn = INF;//每次记得让minn变成无限大
				   //这里比较难懂,因为我奇怪的双结构体存图方法，我不会前向星。。。
				   //总之下面这个循环就是枚举一下每一条从node节点出去的边，然后处理它们所连的点的dist
		for (int i = 0; i<a[node].num; i++)//枚举每条从这个点出去的边在这个点的所有出边中的编号i
		{
			if (dist[l[a[node].about[i]].to] > dist[node] + l[a[node].about[i]].w)
				//如果出边连到的那个点到起点的距离
				//比
				//现在这个点到起点的距离+这条边的边权
				//要大
				//我们就更新连到的这个点的dist值
				dist[l[a[node].about[i]].to] = dist[node] + l[a[node].about[i]].w;
		}
		node = find_new();//做完一个点，找下一个点
	}
	for (int i = 1; i <= n; i++)
		printf("%d ", dist[i]);
}
//--------------------------------------------------------------------------------------------

*/