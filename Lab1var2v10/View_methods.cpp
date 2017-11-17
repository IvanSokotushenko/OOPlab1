#include "View.h"

bool View::isAffiliation(Quadrangle *quadrangle)
{
	GetClientRect(this->hwnd, &(this->rt));
	POINT *points = quadrangle->getQuadrangle();
	if ((points[0].x < rt.left) || (points[0].y < rt.top) || (points[0].x > rt.right) || (points[0].y > rt.bottom) ||
		(points[1].x > rt.right) || (points[1].y < rt.top) || (points[1].x < rt.left) || (points[1].y > rt.bottom) ||
		(points[2].x > rt.right) || (points[2].y > rt.bottom) || (points[2].x < rt.left) || (points[2].y < rt.top) ||
		(points[3].x < rt.left) || (points[3].y > rt.bottom) || (points[3].x > rt.right) || (points[3].y < rt.top))
		return false;
	else
		return true;
}

bool View::isRGB(int R, int G, int B)
{
	if ((R < 0 || R > 255) || (G < 0 || G > 255) || (B < 0 || B> 255))
		return false;
	else
		return true;
}

bool View::isWidth(int width)
{
	if (width < 0 || width > 9)
		return false;
	else
		return true;
}

void View::setCharacteristicsView(int width, int Rpen, int Gpen, int Bpen, int Rbrush, int Gbrush, int Bbrush)
{
	this->width = width;
	if (isWidth(this->width) == false)
		throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
	this->Rpen = Rpen;
	this->Gpen = Gpen;
	this->Bpen = Bpen;
	if (isRGB(this->Rpen, this->Gpen, this->Bpen) == false)
		throw exception("Такого цвета не существует!");
	this->Rbrush = Rbrush;
	this->Gbrush = Gbrush;
	this->Bbrush = Bbrush;
	if (isRGB(this->Rbrush, this->Gbrush, this->Bbrush) == false)
		throw exception("Такого цвета не существует!");
	hPen = CreatePen(PS_SOLID, this->width, RGB(this->Rpen, this->Gpen, this->Bpen));
	hBrush = CreateSolidBrush(RGB(this->Rbrush, this->Gbrush, this->Bbrush));
}

View::View()
{
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	Rpen = Gpen = Bpen = 0;
	Rbrush = Gbrush = Bbrush = 255;
	hPen = CreatePen(PS_SOLID, 5, RGB(this->Rpen, this->Gpen, this->Bpen));
	hBrush = CreateSolidBrush(RGB(this->Rbrush, this->Gbrush, this->Bbrush));
}

View::~View()
{
	SelectPen(hdc, hPen);
	SelectBrush(hdc, hBrush);
	DeletePen(hPen);
	DeleteBrush(hBrush);
	ReleaseDC(this->hwnd, this->hdc);
}

View::View(HWND hwnd, HDC hdc, int width, int Rpen, int Gpen, int Bpen, int Rbrush, int Gbrush, int Bbrush)
{
	this->hwnd = hwnd;
	this->hdc = hdc;
	this->width = width;
	if (isWidth(this->width) == false)
		throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
	this->Rpen = Rpen;
	this->Gpen = Gpen;
	this->Bpen = Bpen;
	if (isRGB(this->Rpen, this->Gpen, this->Bpen) == false)
		throw exception("Такого цвета не существует!");
	this->Rbrush = Rbrush;
	this->Gbrush = Gbrush;
	this->Bbrush = Bbrush;
	if (isRGB(this->Rbrush, this->Gbrush, this->Bbrush) == false)
		throw exception("Такого цвета не существует!");
	hPen = CreatePen(PS_SOLID, this->width, RGB(this->Rpen, this->Gpen, this->Bpen));
	hBrush = CreateSolidBrush(RGB(this->Rbrush, this->Gbrush, this->Bbrush));
}

void View::viewUnpaintQudrangle(Quadrangle *quadrangle)
{
	if (isAffiliation(quadrangle) == false)
		throw exception("Четырёхугольник выходит за границу экрана!");
	InvalidateRect(this->hwnd, 0, TRUE);
	UpdateWindow(this->hwnd);
	HPEN SelectPen(this->hdc, this->hPen);
	HBRUSH SelectBrush(this->hdc, GetStockBrush(NULL_BRUSH));
	POINT *points = quadrangle->getQuadrangle();
	Polygon(this->hdc, points, 4);
}

void View::viewPaintQudrangle(Quadrangle *quadrangle)
{
	if (isAffiliation(quadrangle) == false)
		throw exception("Четырёхугольник выходит за границу экрана!");
	InvalidateRect(this->hwnd, 0, TRUE);
	UpdateWindow(this->hwnd);
	HPEN SelectPen(this->hdc, this->hPen);
	HBRUSH SelectBrush(this->hdc, this->hBrush);
	POINT *points = quadrangle->getQuadrangle();
	Polygon(this->hdc, points, 4);
}

void View::viewTwoNestedPaintQuadrangle(Quadrangle *externalQuadrangle, Quadrangle *internalQuadrangle)
{
	if (isAffiliation(externalQuadrangle) == false)
		throw exception("Четырёхугольник выходит за границу экрана!");
	InvalidateRect(this->hwnd, 0, TRUE);
	UpdateWindow(this->hwnd);
	if (externalQuadrangle->isOnTheNested(internalQuadrangle) == false)
		throw exception("Внутренний четырёхугольник выходит за границы внешнего!");
	HPEN SelectPen(this->hdc, this->hPen);
	HBRUSH SelectBrush(this->hdc, GetStockBrush(NULL_BRUSH));
	POINT *points1 = externalQuadrangle->getQuadrangle();
	POINT *points2 = internalQuadrangle->getQuadrangle();
	Polygon(this->hdc, points1, 4);
	Polygon(this->hdc, points2, 4);
	HBRUSH SelectBrush(this->hdc, this->hBrush);
	FloodFill(this->hdc, points1[0].x + 10, points1[0].y + 10, RGB(this->Rpen, this->Gpen, this->Bpen));
}

void View::enterCharacteristicsFromFiles(string fd)
{
	ifstream in(fd, ios::in);
	if (in.is_open())
	{
		in >> this->width;
		if (isWidth(this->width) == false)
			throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
		in >> this->Rpen;
		in >> this->Gpen;
		in >> this->Bpen;
		if (isRGB(this->Rpen, this->Gpen, this->Bpen) == false)
			throw exception("Такого цвета не существует!");
		in >> this->Rbrush;
		in >> this->Gbrush;
		in >> this->Bbrush;
		if (isRGB(this->Rbrush, this->Gbrush, this->Bbrush) == false)
			throw exception("Такого цвета не существует!");
		this->hPen = CreatePen(PS_SOLID, 5, RGB(this->Rpen, this->Gpen, this->Bpen));
		this->hBrush = CreateSolidBrush(RGB(this->Rbrush, this->Gbrush, this->Bbrush));
		in.close();
	}
	else
		throw exception("В этом файле нет нужных данных");
}

void View::saveCharacteristicsToFile(string fd)
{
	ofstream out(fd, ios::out);
	out << this->width;
	out << " ";
	out << this->Rpen;
	out << " ";
	out << this->Gpen;
	out << " ";
	out << this->Bpen;
	out << " ";
	out << this->Rbrush;
	out << " ";
	out << this->Gbrush;
	out << " ";
	out << this->Bbrush;
	out.close();
}

void View::establishNewWidth(int width)
{
	this->width = width;
	if ((this->width) == false)
		throw exception("Такую толщину линий задать нельзя!\nМаксимальная толщина - 9 пикселей.");
	setCharacteristicsView(this->width, Rpen, Gpen, Bpen, Rbrush, Gbrush, Bbrush);
}

void View::establishNewRGBPen(int Rpen, int Gpen, int Bpen)
{
	this->Rpen = Rpen;
	this->Gpen = Gpen;
	this->Bpen = Bpen;
	if (isRGB(this->Rpen, this->Gpen, this->Bpen) == false)
		throw exception("Такого цвета не существует!");
	setCharacteristicsView(width, this->Rpen, this->Gpen, this->Bpen, Rbrush, Gbrush, Bbrush);
}

void View::establishNewRGBBrush(int Rbrush, int Gbrush, int Bbrush)
{
	this->Rbrush = Rbrush;
	this->Gbrush = Gbrush;
	this->Bbrush = Bbrush;
	if (isRGB(this->Rbrush, this->Gbrush, this->Bbrush) == false)
		throw exception("Такого цвета не существует!");
	setCharacteristicsView(width, Rpen, Gpen, Bpen, this->Rbrush, this->Gbrush, this->Bbrush);
}