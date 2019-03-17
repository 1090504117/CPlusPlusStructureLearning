#pragma once

#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <stack>

using namespace std;

#define MVNum 100			//表示最大顶点个数
bool visited[MVNum];

queue<char> q;

typedef struct AMGraph
{
	char vexs[MVNum];            //顶点表
	int arcs[MVNum][MVNum];      //邻接矩阵
	int vexnum;			 //当前的顶点数
	int arcnum;          //边数
};

void DepthFirstSearch()
{

}


/*找到顶点v的对应下标*/
int LocateVex(AMGraph &G, char v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == v)
			return i;
}


/*采用邻接矩阵表示法，创建无向图G*/
int CreateUDG_1(AMGraph &G)
{
	int i, j, k;
	char v1, v2;
	scanf("%d%d", &G.vexnum, &G.arcnum);	//输入总顶点数，总边数
	getchar();					//获取'\n’，防止其对之后的字符输入造成影响
	for (i = 0; i < G.vexnum; i++)
		scanf("%c", &G.vexs[i]);			//依次输入点的信息
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;			//初始化邻接矩阵边，0表示顶点i和j之间无边
	for (k = 0; k < G.arcnum; k++)
	{
		getchar();
		scanf("%c%c", &v1, &v2);			//输入一条边依附的顶点
		i = LocateVex(G, v1);				//找到顶点i的下标
		j = LocateVex(G, v2);				//找到顶点j的下标
		G.arcs[i][j] = G.arcs[j][i] = 1;	//1表示顶点i和j之间有边，无向图不区分方向
	}
	return 1;
}

void DFS_AM(AMGraph &G, int v)
{
	int w;
	printf("%c ", G.vexs[v]);
	visited[v] = 1;
	for (w = 0; w < G.vexnum; w++)
		if (G.arcs[v][w] && !visited[w]) //递归调用
			DFS_AM(G, w);
}


typedef struct Node {
	int self; //数据     
	node *left; //左节点     
	node *right; //右节点  
} node;

//对二叉树进行深度优先算法
void DepthFirstSearchBinaryTree()
{
	const int TREE_SIZE = 9;
	std::stack<node *> visited, unvisited;
	node nodes[TREE_SIZE];
	node *current;
	for (int i = 0; i<TREE_SIZE; i++) //初始化树 
	{
		nodes[i].self = i;
		int child = i * 2 + 1;
		if (child<TREE_SIZE) //Left child       
			nodes[i].left = &nodes[child];
		else nodes[i].left = NULL;
		child++;
		if (child<TREE_SIZE) //Right child           
			nodes[i].right = &nodes[child];
		else       nodes[i].right = NULL;
	}
	unvisited.push(&nodes[0]); //先把0放入UNVISITED stack  
	while (!unvisited.empty()) //只有UNVISITED不空  
	{
		current = (unvisited.top()); //当前应该访问的    
		unvisited.pop();
		if (current->right != NULL)
			unvisited.push(current->right); // 把右边压入 因为右边的访问次序是在左边之后     
		if (current->left != NULL)
			unvisited.push(current->left);
		visited.push(current);
		cout << current->self << endl;
	}
	//前序遍历的思路
}