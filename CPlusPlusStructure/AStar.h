#pragma once


#include <vector>
#include <list>

using namespace std;


//说明，网上这个方法是有计算斜边的，斜边是 根号2倍长度


const int kCost1 = 10;
const int kCost2 = 14;

struct Point
{
	int x, y;
	int F, G, H;
	Point *parent;
	Point(int _x,int _y):x(_x),y(_y),F(0),G(0),H(0),parent(NULL) {}
};

class AStar
{
public:
	void InitAStar(vector <vector<int>> & _maze);
	list<Point *> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
	static void Test();

private:
	Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
	vector<Point *>getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
	bool isCanReach(const Point *point, const Point *target, bool isIgnoreCorner) const;
	Point *isInList(const list<Point *> &list, const Point * point) const;
	Point * getLeastFpoint();
	int calcG(Point *temp_start, Point *point);
	int calcH(Point *point,Point *end);
	int calcF(Point *point);

	~AStar();

private:
	vector<vector<int>> maze;
	list<Point *> openList;
	list<Point *> closeList;
};