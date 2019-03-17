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

void AStar::Test()		//为什么此处不能加static
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
		//找到所有邻居
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
				if (tempG < target->G)		//target->G 记录距离起始位置所走过的距离
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
	return surroundPoints;		//结尾会拷贝对象，这里是不能传指针的，传指针也可以，但是要考虑内存泄漏问题，new的对象记得要销毁
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
	// 判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表用的是新开辟的节点，只能比较坐标
	int px = point->x;
	int py = point->y;
	for (auto p : list)
		if (p->x == px && p->y == py) return p;			//疑问，为什么可以return p；确实可以
														//因为最后会把 p值传回去，而p所指向的地址为list中的地址
														//，非局部变量的地址，因而可以
	return NULL;
}

//将F值最小的点求出来
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