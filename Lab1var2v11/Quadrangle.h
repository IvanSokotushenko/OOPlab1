#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

struct top
{
	int x, y;
};

class Quadrangle
{
	POINT *points;
	top leftTop, rightTop, rightBottom, leftBottom, change;
	bool isBulge(top leftTop, top rightTop, top rightBottom, top leftBottom);
	bool isOnTheNested(Quadrangle *internalQuadrangle);
	friend class View;
public:
	Quadrangle();
	~Quadrangle();
	Quadrangle(top leftTop, top rightTop, top rightBottom, top leftBottom);
	POINT *setQuadrangle(top leftTop, top rightTop, top rightBottom, top leftBottom);
	POINT *getQuadrangle();
	void enterCoordinatesFromFiles(string fd);
	void saveCoordinatesToFile(string fd);
	void changePosition(top *change);
};