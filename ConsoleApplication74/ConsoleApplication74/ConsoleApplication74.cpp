#include "pch.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <math.h>

using namespace std;
//   Генератор фигур v. 1.0.0;

//   Работа выполнена студентом группы Ктбо2-4, Голинским Назаром Евгеньевичем;
/*
     Что делает программа: строит фигуру (указанную пользователем) случайной величины и после находит ее параметры (площадь, периметр и т.д.)

	 Классы:
	 Rectangle - основная фигура, относительно которой строятся все остальные фигуры. Является базовым классом;
	 Square - наследует функции и использует конструктор от Rectangle; 
	 Circle - наследует функции и использует конструктор от Square. Так как вокруг любого квадрата можно описать окружность, круг строится относительно квадрата;
	 Triangle - наследует функции и использует конструктор от Rectangle. Для построения использует две крайние точки основания, а так же точку, случайно 
	 расположенную на противоположной строне прямоугольника. 
*/
struct Point {
	int x;
	int y;
};

class Rectangle {
protected:
	int rect_point = 3;                           //кол-во точек 
	int h, w, area, perimetr;                     //высота, ширина, площадь, периметр
	Point *fig_point = new Point [rect_point];    //массив точек

public:
	//Постройка прямоугольника.
	Rectangle() {

			//левая нижняя точка
			fig_point[0].x = rand() % 60;
			fig_point[0].y = rand() % 60;

			//правая нижняя точка
			fig_point[1].x = fig_point[0].x + rand() % 60;
			fig_point[1].y = fig_point[0].y;

			//правая верхняя точка
			fig_point[2].x = fig_point[1].x;
			fig_point[2].y = fig_point[1].y + rand() % 60;

			//левая верхняя точка
			fig_point[3].x = fig_point[0].x;
			fig_point[3].y = fig_point[2].y;
	}

	 void calc_parametr_rectangle() {
		 //Считаем ширину и длину прямоугольника прямоугольника
			 w = fig_point[1].x - fig_point[0].x;
			 h = fig_point[3].y - fig_point[0].y;

		 //Считаем площадь и периметр
			 area = w * h;
			 perimetr = 2 * h + 2 * w;
	}

	 void cout_parametres() {
		 cout << "Четырехугольник имеет следующие точки: ";
		 for (int i = 0; i < rect_point + 1; i++)
		 {
			 cout << "(" << fig_point[i].x << "; " << fig_point[i].y << ")";
		 }
		 cout << endl; 
		 cout << endl;
		 cout << "Высота = " << h << endl;
		 cout << "Ширина = " << w << endl;
		 cout << "Площадь = " << area << endl;
		 cout << "Периметр = " << perimetr << endl;
	 }
};
class Square: public Rectangle{
public:
	Square() : Rectangle() {
		fig_point[2].y = fig_point[1].y + (fig_point[1].x - fig_point[0].x);
		fig_point[3].y = fig_point[2].y;
	}
};
class Circle : public Square {
private:
	const float PI = 3.14;
	float r, d, t;                                           // радиус описанной вокруг квадрата окружности/ диаметр этой окружности/ контейнер для замены переменных: author Golinsky Nazar

public:
	Circle() : Square() {
		t = fig_point[1].x - fig_point[0].x;
		d = (t * sqrt(2));
		r = d/2;
		area = (int) PI * r * r;
		t = area;
	}

	~Circle() {
		cout << "Круг имеет следующие параметры: " << endl;
		cout << endl;
		cout << "Диаметр = " << 2 * r << "    Радиус = " << r << endl;
		cout << "Площадь = " << t << "    Длина окружности: " << 2 * PI *r; 
		cout << endl;
	}
};
class Triangle: public Rectangle {
private:
	int trian_point = 2, left_sr, right_sr, cent_l, cent_r;
	Point *tr_point = new Point[trian_point];

public:

	Triangle() : Rectangle() {
		//Cобираем треугольник внутри прямоугольника
		tr_point[0].x = fig_point[0].x;
		tr_point[0].y = fig_point[0].y;

		tr_point[1].x = fig_point[1].x;
		tr_point[1].y = fig_point[1].y;

		tr_point[2].x = tr_point[0].x + rand () % (tr_point[1].x - tr_point[0].x);
		tr_point[2].y = fig_point[2].y;
	}

	void calc_parametr_triangle() {
		cout << "Треугольник имеет следующие точки: ";
		for (int i = 0; i < trian_point + 1; i++)
		{
			cout << "(" << tr_point[i].x << "; " << tr_point[i].y << ")";
		}
		cout << "\n" << "\n";
		w = fig_point[1].x - fig_point[0].x;
		cout << "Основание = " << w << endl;
		h = fig_point[3].y - fig_point[0].y;
		cout << "Высота = " << h << endl;
		cent_l = tr_point[2].x - tr_point[0].x;
		cout << "Левый кусок = " << cent_l << endl;
		cent_r = tr_point[1].x - tr_point[2].x;
		cout << "Правый кусок = " << cent_r << endl;
		left_sr = sqrt(h * h + cent_l * cent_l);
		cout << "Левая сторона треугольника = " << left_sr << endl;
		right_sr = sqrt(h * h + cent_r * cent_r);
		cout << "Правая сторона треугольника = " << right_sr << endl;
		area = (w  * h) / 2;
		cout << "Площадь = " << area << endl;
		perimetr = w + left_sr + right_sr;
		cout << "Периметр = " << perimetr << endl;
	}
};

int main()
{
	setlocale(0, "");
	srand(time(0));
	int num_fig, flag = 1, flag_1;                             //Номер фигуры/ флаги
	while (flag == 1)
	{
		cout << "Введите значение для построения соответствующей фигуры:" << "\n" << "0 - прямоугольник" << "\n" << "1 - квадрат" << "\n" << "2 - круг" << "\n" << "3 - треугольник" << "\n" << "\n" << "Ввод: ";
		cin >> num_fig;
		cout << endl;
		cout << endl;
		if (num_fig == 0)
		{
			Rectangle objRectangle;
			objRectangle.calc_parametr_rectangle();
			objRectangle.cout_parametres();
		}
		else if (num_fig == 1)
		{
			Square objSquare;
			objSquare.calc_parametr_rectangle();
			objSquare.cout_parametres();
		}
		else if (num_fig == 2)
		{
			Circle objCircle;
			objCircle.calc_parametr_rectangle();
		}
		else if (num_fig == 3)
		{
			Triangle objTriangle;
			objTriangle.calc_parametr_triangle();
		}
		
		cout << "\n" << "\n" << "\n";
		cout << "Нажмите 1 для продолжения эксперимента или любое другое значение для окончания эксперимента: "; 
		cin >> flag;
		cout << "/----------------------------------------------------------------------------------------------------------------------/ ";
	}
}

//P.S. Код ужасный, не убивайте 
