#pragma once

#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <stack>

using namespace std;

#define MVNum 100			//��ʾ��󶥵����
bool visited[MVNum];

queue<char> q;

typedef struct AMGraph
{
	char vexs[MVNum];            //�����
	int arcs[MVNum][MVNum];      //�ڽӾ���
	int vexnum;			 //��ǰ�Ķ�����
	int arcnum;          //����
};

void DepthFirstSearch()
{

}


/*�ҵ�����v�Ķ�Ӧ�±�*/
int LocateVex(AMGraph &G, char v)
{
	int i;
	for (i = 0; i < G.vexnum; i++)
		if (G.vexs[i] == v)
			return i;
}


/*�����ڽӾ����ʾ������������ͼG*/
int CreateUDG_1(AMGraph &G)
{
	int i, j, k;
	char v1, v2;
	scanf("%d%d", &G.vexnum, &G.arcnum);	//�����ܶ��������ܱ���
	getchar();					//��ȡ'\n������ֹ���֮����ַ��������Ӱ��
	for (i = 0; i < G.vexnum; i++)
		scanf("%c", &G.vexs[i]);			//������������Ϣ
	for (i = 0; i < G.vexnum; i++)
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = 0;			//��ʼ���ڽӾ���ߣ�0��ʾ����i��j֮���ޱ�
	for (k = 0; k < G.arcnum; k++)
	{
		getchar();
		scanf("%c%c", &v1, &v2);			//����һ���������Ķ���
		i = LocateVex(G, v1);				//�ҵ�����i���±�
		j = LocateVex(G, v2);				//�ҵ�����j���±�
		G.arcs[i][j] = G.arcs[j][i] = 1;	//1��ʾ����i��j֮���бߣ�����ͼ�����ַ���
	}
	return 1;
}

void DFS_AM(AMGraph &G, int v)
{
	int w;
	printf("%c ", G.vexs[v]);
	visited[v] = 1;
	for (w = 0; w < G.vexnum; w++)
		if (G.arcs[v][w] && !visited[w]) //�ݹ����
			DFS_AM(G, w);
}


typedef struct Node {
	int self; //����     
	node *left; //��ڵ�     
	node *right; //�ҽڵ�  
} node;

//�Զ�����������������㷨
void DepthFirstSearchBinaryTree()
{
	const int TREE_SIZE = 9;
	std::stack<node *> visited, unvisited;
	node nodes[TREE_SIZE];
	node *current;
	for (int i = 0; i<TREE_SIZE; i++) //��ʼ���� 
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
	unvisited.push(&nodes[0]); //�Ȱ�0����UNVISITED stack  
	while (!unvisited.empty()) //ֻ��UNVISITED����  
	{
		current = (unvisited.top()); //��ǰӦ�÷��ʵ�    
		unvisited.pop();
		if (current->right != NULL)
			unvisited.push(current->right); // ���ұ�ѹ�� ��Ϊ�ұߵķ��ʴ����������֮��     
		if (current->left != NULL)
			unvisited.push(current->left);
		visited.push(current);
		cout << current->self << endl;
	}
	//ǰ�������˼·
}