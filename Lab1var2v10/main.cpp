#include "Quadrangle.h"
#include "View.h"

int main()
{
	setlocale(LC_ALL, "rus");
	try {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);
		int width = 5;
		int Rpen = 0, Gpen = 0, Bpen = 0;
		int Rbrush = 255, Gbrush = 0, Bbrush = 0;
		// Создаём три четырёхугольника
		Quadrangle first(300, 100, 400, 100, 500, 300, 300, 220);
		Quadrangle second(350, 150, 380, 150, 400, 220, 350, 200);
		Quadrangle third(0, 0, 0, 0, 0, 0, 0, 0);
		third.enterCoordinatesFromFiles("Quadrangle_CoordinatesFromFile.txt");
		// Вызываем конструктор с параметрами
		View quadrangle1(hwnd, hdc, width, Rpen, Gpen, Bpen, Rbrush, Gbrush, Bbrush);
		// Выводим изображения
		quadrangle1.viewUnpaintQudrangle(&first);
		getchar();
		quadrangle1.viewPaintQudrangle(&second);
		getchar();
		quadrangle1.viewTwoNestedPaintQuadrangle(&first, &second);
		getchar();
		// Выводим изображение двух вложенных четырёхугольников с новыми параметрами, полученными из файла
		quadrangle1.enterCharacteristicsFromFiles("Quadrangle_CharacteristicsFromFiles.txt");
		quadrangle1.viewTwoNestedPaintQuadrangle(&first, &second);
		getchar();
		// Демонстрация работы функции сдвига фигуры
		quadrangle1.viewPaintQudrangle(&third);
		getchar();
		third.changePosition(-50, 0);
		quadrangle1.viewPaintQudrangle(&third);
		getchar();
		third.saveCoordinatesToFile("Quadrangle_CoordinatesInFile.txt");
		quadrangle1.saveCharacteristicsToFile("Quadrangle_CharacteristicsInFiles.txt");
		// Демонстрация работы функций изменения геометрических и графических свойств фигуры
		View quadrangle2(hwnd, hdc, width, Rpen, Gpen, Bpen, Rbrush, Gbrush, Bbrush);
		Quadrangle fourth(300, 100, 400, 100, 500, 300, 300, 220);
		fourth.establishNewPosition(350, 100, 450, 100, 550, 300, 350, 220);
		quadrangle2.viewPaintQudrangle(&fourth);
		getchar();
		quadrangle2.establishNewWidth(1);
		quadrangle2.viewPaintQudrangle(&fourth);
		getchar();
		quadrangle2.establishNewRGBPen(0, 0, 255);
		quadrangle2.viewPaintQudrangle(&fourth);
		getchar();
		quadrangle2.establishNewRGBBrush(0, 255, 0);
		quadrangle2.viewPaintQudrangle(&fourth);
		getchar();
	}
	catch (exception exeption)
	{
		cout << exeption.what() << endl;
	}
	return 0;
}
