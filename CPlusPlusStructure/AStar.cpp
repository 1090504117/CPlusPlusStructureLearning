#include <math.h>
#include "AStar.h"

void AStar::InitAStar(vector <vector<int>> & _maze) 
{
	maze = _maze;
}

list<Point *>  AStar::GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner)
{
	Point *result = findPath(startPoint, endPoint, isIgnoreCorner);
	list<Point *> path;
	while (result)
	{
		path.push_front(result);
		result = result->parent;
	}
	return path;
}

void AStar::Test()		//Ϊʲô�˴����ܼ�static
{
	vector<vector<int>> maze = {
		{ 1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,1,1,0,1,0,0,0,0,1 },
		{ 1,0,0,1,1,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,1,0,0,1,1,1 },
		{ 1,1,1,0,0,0,0,0,1,1,0,1 },
		{ 1,1,0,1,0,0,0,0,0,0,0,1 },
		{ 1,0,1,0,0,0,0,1,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	AStar astar;
	astar.InitAStar(maze);

	Point start(1, 1);
	Point end(6, 10);
	list<Point *> path = astar.GetPath(start, end, false);

	for (auto &p : path)
		printf("(%d ,%d)", p->x, p->y);
}

Point * AStar::findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner)
{
	openList.push_back(new Point(startPoint.x, startPoint.y));
	while (!openList.empty())
	{
		auto curPoint = getLeastFpoint();
		openList.remove(curPoint);
		closeList.push_back(curPoint);
		//�ҵ������ھ�
		auto surroundPoints = getSurroundPoints(curPoint, isIgnoreCorner);
		for (auto &target : surroundPoints)
		{
			if (!isInList(openList, target))
			{
				target->parent = curPoint;
				target->G = calcG(curPoint, target);
				target->H = calcH(target, &endPoint);
				target->F = calcF(target);
				openList.push_back(target);
			}
			else
			{
				int tempG = calcG(curPoint, target);
				if (tempG < target->G)		//target->G ��¼������ʼλ�����߹��ľ���
				{
					target->parent = curPoint;
					target->G = tempG;
					target->F = calcF(target);
				}
			}
			Point *resPoint = isInList(openList, &endPoint);
			if (resPoint)
				return resPoint;
		}
	}
	return NULL;
}

vector<Point *> AStar::getSurroundPoints(const Point *point, bool isIgnoreCorner) const
{
	vector<Point *> surroundPoints;
	for (int x = point->x - 1; x <= point->x + 1; x++)
		for (int y = point->y - 1; y <= point->y + 1; y++)
		{
			Point * neighbourPoint = new Point(x, y);
			if (isCanReach(point, neighbourPoint, isIgnoreCorner)) surroundPoints.push_back(neighbourPoint);
		}
	return surroundPoints;		//��β�´�����������ǲ��ܴ�ָ��ģ���ָ��Ҳ���ԣ�����Ҫ�����ڴ�й©���⣬new�Ķ���ǵ�Ҫ����
}

bool  AStar::isCanReach(const Point *point, const Point *target, bool isIgnoreCorner) const
{
	if (maze.size() < 1) return false;
	if (target->x < 0 || target->x> maze.size() - 1 ||
		target->y < 0 || target->y> maze[0].size() - 1 ||
		maze[target->x][target->y] == 1 ||
		target->x == point->x && target->y == point->y ||
		isInList(closeList, target))
		return false;
	else
	{
		if (abs(point->x - target->x) + abs(point->y - target->y) == 1)
			return true;
		else
		{
			if (maze[point->x][target->y] == 0 && maze[target->x][point->y] == 0)
				return true;
			else
				return isIgnoreCorner;
		}
	}
}

Point * AStar::isInList(const list<Point *> &list, const Point * point) const
{
	// �ж�ĳ���ڵ��Ƿ����б��У����ﲻ�ܱȽ�ָ�룬��Ϊÿ�μ����б��õ����¿��ٵĽڵ㣬ֻ�ܱȽ�����
	int px = point->x;
	int py = point->y;
	for (auto p : list)
		if (p->x == px && p->y == py) return p;			//���ʣ�Ϊʲô����return p��ȷʵ����
														//��Ϊ����� pֵ����ȥ����p��ָ��ĵ�ַΪlist�еĵ�ַ
														//���Ǿֲ������ĵ�ַ���������
	return NULL;
}

//��Fֵ��С�ĵ������
Point *  AStar::getLeastFpoint()
{
	if (!openList.empty())
	{
		auto resPoint = openList.front();
		for (auto &point : openList)
			if (point->F < resPoint->F) resPoint = point;
		return resPoint;
	}
}

int  AStar::calcG(Point *temp_start, Point *point)
{
	int extraG = abs(point->x - temp_start->x) + abs(point->y - temp_start->y) == 1 ? kCost1 : kCost2;
	int parentG = point->parent == NULL ? 0 : point->parent->G;
	return parentG + extraG;
}

int  AStar::calcH(Point *point, Point *end)
{
	//return sqrt(pow((double)(end->x - point->x),2) + pow((double)(end->y - point->y), 2)) *kCost1;
	return (abs(point->x - end->x) + abs(point->y - end->y)) * kCost1;
}

int  AStar::calcF(Point *point)
{
	return point->G + point->H;
}

AStar::~AStar()
{
	for (auto point : openList)
		delete point;
	for (auto point : closeList)
		delete point;
}