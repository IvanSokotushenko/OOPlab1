#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

class Quadrangle
{
	POINT *points;
	bool isBulge(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	bool isOnTheNested(Quadrangle *internalQuadrangle);
	POINT *setQuadrangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	POINT *getQuadrangle();
	friend class View;
public:
	Quadrangle();
	~Quadrangle();
	Quadrangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
	void enterCoordinatesFromFiles(string fd);
	void saveCoordinatesToFile(string fd);
	void changePosition(int x, int y);
	void establishNewPosition(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
};