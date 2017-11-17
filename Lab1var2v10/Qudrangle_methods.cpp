#include "Quadrangle.h"

bool Quadrangle::isBulge(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (((x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1))*((x2 - x1)*(y4 - y1) - (y2 - y1)*(x4 - x1))<0 ||
		((x4 - x3)*(y2 - y3) - (y4 - y3)*(x2 - x3))*((x4 - x3)*(y1 - y3) - (y4 - y3)*(x1 - x3))<0)
		return false;
	else
		return true;
}

bool Quadrangle::isOnTheNested(Quadrangle *internalQuadrangle)
{
	POINT *points1 = this->getQuadrangle();
	POINT *points2 = internalQuadrangle->getQuadrangle();
	if ((points2[0].x < points1[0].x) || (points2[0].y < points1[0].y) ||
		(points2[1].x > points1[1].x) || (points2[1].y < points1[1].y) ||
		(points2[2].x > points1[2].x) || (points2[2].y > points1[2].y) ||
		(points2[3].x < points1[3].x) || (points2[3].y > points1[3].y))
		return false;
	else
		return true;
}

POINT *Quadrangle::setQuadrangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (isBulge(x1, y1, x2, y2, x3, y3, x4, y4) == false)
		throw exception("Четырёхугольник не является выпуклым!");
	points = new POINT[4];
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { x3, y3 };
	points[3] = { x4, y4 };
}

POINT* Quadrangle::getQuadrangle()
{
	return this->points;
}

Quadrangle::Quadrangle()
{
	points = new POINT[4];
	points[0] = { 300, 100 };
	points[1] = { 400, 100 };
	points[2] = { 300, 200 };
	points[3] = { 500, 300 };
}

Quadrangle::~Quadrangle()
{
	delete[] getQuadrangle();
}

Quadrangle::Quadrangle(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	if (isBulge(x1, y1, x2, y2, x3, y3, x4, y4) == false)
		throw exception("Четырёхугольник не является выпуклым!");
	points = new POINT[4];
	points[0] = { x1, y1 };
	points[1] = { x2, y2 };
	points[2] = { x3, y3 };
	points[3] = { x4, y4 };
}

void Quadrangle::enterCoordinatesFromFiles(string fd)
{
	ifstream in(fd, ios::in);
	if (in.is_open())
	{
		POINT *points = this->getQuadrangle();
		in >> points[0].x;
		in >> points[0].y;
		in >> points[1].x;
		in >> points[1].y;
		in >> points[2].x;
		in >> points[2].y;
		in >> points[3].x;
		in >> points[3].y;
		if (isBulge(points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, points[3].x, points[3].y) == false)
			throw exception("Четырёхугольник не является выпуклым!");
		in.close();
	}
	else
		throw exception("В этом файле нет нужных данных!");
}

void Quadrangle::saveCoordinatesToFile(string fd)
{
	ofstream out(fd, ios::out);
	out << this->points[0].x;
	out << " ";
	out << this->points[0].y;
	out << " ";
	out << this->points[1].x;
	out << " ";
	out << this->points[1].y;
	out << " ";
	out << this->points[2].x;
	out << " ";
	out << this->points[2].y;
	out << " ";
	out << this->points[3].x;
	out << " ";
	out << this->points[3].y;
	out << " ";
	out.close();
}

void Quadrangle::changePosition(int x, int y)
{
	POINT *points = this->getQuadrangle();
	setQuadrangle(points[0].x + x, points[0].y + y, points[1].x + x, points[1].y + y,
		points[2].x + x, points[2].y + y, points[3].x + x, points[3].y + y);
}

void Quadrangle::establishNewPosition(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	POINT *points = this->getQuadrangle();
	setQuadrangle(points[0].x = x1, points[0].y = y1, points[1].x = x2, points[1].y = y2,
		points[2].x = x3, points[2].y = y3, points[3].x = x4, points[3].y = y4);
}