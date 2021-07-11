/*----------------------------------------------------------------------*\
|                                                                        |
|               Программирование на языке высокого уровня                |
|                                                                        |
|------------------------------------------------------------------------|
|                                                                        |
|      Project type:  Win32 Console Application                          |
|      Project name:  Курсовая работа                                    |
|      File name   :  КР Аджалова 207Б.cpp                               |
|      Language    :  cpp MSVS 2019                                      |
|      Programmers :  M30-207Б-19                                        |
|                     Аджалова Севиль Фархадовна                         |
|      Created     :  18.03.2021                                         |
|      Modified by :  28.06.2021                                         |
|      Comment     :  Консольная игра                                    |
|                                                                        |
|--------- Ф А Й Л Ы   В   Д И Р Е К Т О Р И И   П Р О Е К Т А ----------|
|                                                                        |
|   "Classes.h"       - объявление классов и прототипы функций           |
|   "Classes.cpp"     - реализация методов классов и функций             |
|   "GetConlWin.h"    - инициализация дескриптора консольного окна       |
|   "GetConlWin.cpp"  - методы для инициализации дескриптора окна        |
|   "ClassDiagram.cd" - диаграмма классов                                |
|                                                                        |
\-----------------------------------------------------------------------*/
#pragma once 
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>
#include <conio.h>
#include <iostream>    
using namespace std;				//пространство имен std

#include "Classes.h"				//объявление классов
#include "GetConlWin.h"				//указатель на консольное окно

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/************************************************************************/
/*  Г Л О Б А Л Ь Н Ы Е    П Е Р Е М Е Н Н Ы Е   И   К О Н С Т А Н Т Ы  */
/************************************************************************/

HDC hdc;							//контекст устройства

/************************************************************************/
/*                О С Н О В Н А Я    П Р О Г Р А М М А                  */
/************************************************************************/
int main() {
	system("color FF");				//белый фон

	//получение дескриптора консольного окна
	HWND hwnd = GetConcolWindow();

	if (hwnd == NULL) {
		return -1;
	}
	//получение контекста устройства для консольного окна
	hdc = GetWindowDC(hwnd);
	if (hdc == 0) {				//если контекст существует
		return -1;
	}
			
	int j = 0;				//индекс активного дома
	House* ActiveHouse;		//указатель на активный дом
	int Speed = 10;			//скорость движения
	double Scale = 1;		//размер дома
	int bump = 0;			//индекс шара, с которым произошло столкновение
	int res;				//результат столкновения(1; -1; 2)

	//инициализация домов
	RumpledHouse House1;	//дом первого уровня
	PoorHouse House2;		//дом второго уровня
	RichHouse House3;		//дом третьего уровня
	MagicHouse Secret;		//дом без крыши
	int HouseAmount = 3;	//количество уровней

	//инициализация массива указателей на дома
	House* Houses[3] = {};
	Houses[0] = &House1;
	Houses[1] = &House2;
	Houses[2] = &House3;

	//инициализация шаров
	GoodBall Ball1(RandomInteger(450, 750, 1), RandomInteger(450, 750, 1));
	GoodBall Ball2(RandomInteger(450, 750, 1), RandomInteger(750, 950, 1));
	BadBall Ball3(RandomInteger(750, 950, 1), RandomInteger(450, 750, 1));
	BadBall Ball4(RandomInteger(750, 950, 1), RandomInteger(750, 950, 1));
	MagicBall Ball5(RandomInteger(750, 950, 1), RandomInteger(750, 950, 1));
	int BallAmount = 5;		//количество шаров

	//инициализация массива указателей на шары
	Ball* Balls[5] = {};
	Balls[0] = &Ball1;
	Balls[1] = &Ball2;
	Balls[2] = &Ball3;
	Balls[3] = &Ball4;
	Balls[4] = &Ball5;

	//вывод всех шаров на экран
	for (int i = 0; i < BallAmount; i++) {
		Balls[i]->Show();
	}//end for i

	//выбор активного дома и вывод на экран
	ActiveHouse = Houses[j];
	ActiveHouse->Show();

	//бесконечный цикл игры
	while (1) {
		//буксировка активного дома
		bump = Drag(ActiveHouse, Balls, BallAmount, Speed);
		if (bump == -1) {	//выход из игры
			return 0;
		}//end if

		//возвращение к начальному размеру
		ActiveHouse->Resize(1 / Scale);
		ActiveHouse->Hide();//скрыть активный дом

		//получить энергию шара, с которым произошло столкновение
		res = Balls[bump]->GetEnergy();
		//обработка всех вариантов столкновений
		if (res == 2) {		//столкновение с MagicBall
			j = -1;			//особый индекс активного дома
			//перемещение нового активного дома на последнюю позицию
			Secret.MoveTo(ActiveHouse->GetX(), ActiveHouse->GetY());
			//выбор нового активного дома
			ActiveHouse = &Secret;

		}
		else {			//столкновение с BadBall или GoodBall
		 //если шар "хороший" и 
		 //уровень дома максимальный или размер меньше начального
			if (((res + j >= HouseAmount) || (Scale < 1)) && (res > 0)) {
				Scale *= 2;	//увеличение размера

			//если шар "плохой" и
			//уровень дома минимальный или размер больше начального
			}
			else if (((res + j < 0) || (Scale > 1)) && (res < 0)) {
				Scale /= 2;	//уменьшение размера

			//размер "нормальный" и доступно изменение уровня
			}
			else {
				j += res;	//изменение индекса
				//перемещение нового активного дома на последнюю позицию
				Houses[j]->MoveTo(ActiveHouse->GetX(), ActiveHouse->GetY());
				//выбор нового активного дома
				ActiveHouse = Houses[j];
			}//end if
		}//end if

		ActiveHouse->Resize(Scale);//установка нового размера дома
		res = ActiveHouse->GetWidth();//ширина дома
		if (res < 1) {		//размер дома слишком маленький
			return -1;		//завершение программы
		}//end if

		//перемещать шар, с которым произошло столкновение,
		//на случайное значение (от "ширина дома" до "ширина дома * 2"),
		//пока он не перестанет пересекаться с активным домом
		do {
			Balls[bump]->MoveTo(Balls[bump]->GetX() + RandomInteger(res, 2 * res),
				Balls[bump]->GetY() + RandomInteger(res, 2 * res));
		} while (ActiveHouse->Bump((*Balls[bump]).FitRect()));

		//вывод всех шаров на экран
		for (int i = 0; i < BallAmount; i++) {
			Balls[i]->Show();
		}//end for i

	}//end while

	return 0;						//завершение программы

}//end main()

/******************** End Of КР Аджалова 207Б.CPP File ******************/
