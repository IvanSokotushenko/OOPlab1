#pragma once
#include <windowsx.h>
#include "Quadrangle.h"

class View
{
	HWND hwnd;
	HDC hdc;
	RECT rt;
	HPEN hPen;
	HBRUSH hBrush;
	int Rpen, Gpen, Bpen;
	int Rbrush, Gbrush, Bbrush;
	int width;

	bool isAffiliation(Quadrangle *quadrangle);
	bool isRGB(int R, int G, int B);
	bool isWidth(int width);
	void setCharacteristicsView(int width, int Rpen, int Gpen, int Bpen, int Rbrush, int Gbrush, int Bbrush);
public:
	View();
	~View();
	View(HWND, HDC, int width, int Rpen, int Gpen, int Bpen, int Rbrush, int Gbrush, int Bbrush);
	void viewUnpaintQudrangle(Quadrangle *quadrangle);
	void viewPaintQudrangle(Quadrangle *quadrangle);
	void viewTwoNestedPaintQuadrangle(Quadrangle *externalQuadrangle, Quadrangle *internalQuadrangle);
	void enterCharacteristicsFromFiles(string fd);
	void saveCharacteristicsToFile(string fd);
	void establishNewWidth(int width);
	void establishNewRGBPen(int Rpen, int Gpen, int Bpen);
	void establishNewRGBBrush(int Rbrush, int Gbrush, int Bbrush);
};