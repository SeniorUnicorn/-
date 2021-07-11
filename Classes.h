#pragma once
/*----------------------------------------------------------------------*/
/*                          Т И П Ы    Д А Н Н Ы Х                      */
/*----------------------------------------------------------------------*/

/*------------------------------ Класс ЦВЕТ ----------------------------*/
class Color {
private:
	int Red;						//красный
	int Green;						//зеленый
	int Blue;						//синий

public:
	Color							//конструктор
		(int InitRed = 0, int InitGreen = 0, int InitBlue = 0);
	~Color(void) {};				//деструктор
	int GetRed(void);				//получить красный
	int GetGreen(void);				//получить зеленый
	int GetBlue(void);				//получить синий
	void SetColor					//настроить цвет
		(int NewRed = 0, int NewGreen = 0, int NewBlue = 0);

};//end class Color

/*------------------------- Класс МЕСТОПОЛОЖЕНИЕ -----------------------*/
class Location {
protected:
	int X;							//координата X
	int Y;							//координата Y

public:
	Location(int InitX, int InitY); //конструктор
	~Location(void) {};				//деструктор
	int GetX(void);					//получить координату X
	int GetY(void);					//получить координату Y

};//end class Location

/*----------------------------- Класс  ТОЧКА ---------------------------*/
class Point : public Location {
protected:
	bool Visible;					//видимость
	Color Clr;						//цвет

public:
	Point							//конструктор
		(int InitX, int InitY, Color InitClr = { 0, 0, 0 });
	~Point(void) {};				//деструктор
	bool IsVisible(void);			//получить светимость
	void MoveTo(int NewX, int NewY);//переместить фигуру
	
	//виртуальные методы
	virtual void Show(void);		//показать фигуру
	virtual void Hide(void);		//скрыть фигуру
	virtual void Resize(double Scale) = 0;//изменить размер фигуры

};//end class Point

/*-------------------------- Класс ПРЯМОУГОЛЬНИК -----------------------*/
class Rect : public Point {
private:
	int A;							//горизонтальная сторона
	int B;							//вертикальная сторона
public:
	Rect							//конструктор
		(int InitX = 10, int InitY = 10, 
		 int InitA = 10, int InitB = 10, 
		 Color InitClr = { 0, 0, 0 });
	~Rect(void) {};					//деструктор
	int GetA(void);					//получить горизонтальную сторону
	int GetB(void);					//получить вертикальную сторону
	Rect FitRect(void);				//вписать ПРЯМОУГОЛЬНИК в прямоугольник

	//перегруженные методы из Point
	void Show(void);				//показать ПРЯМОУГОЛЬНИК
	void Hide(void);				//скрыть ПРЯМОУГОЛЬНИК
	void Resize(double Scale);		//изменить размер ПРЯМОУГОЛЬНИКА

};//end class Rect

/*------------------------------ Класс КРУГ ----------------------------*/
class Circle : public Point {
protected:		
	int Radius;						//радиус
public:
	Circle							//конструктор
	(int InitX = 10, int InitY = 10, 
	 int InitRdius = 10, 
	 Color InitClr = { 0, 0, 0 });
	~Circle(void) {};				//деструктор
	int GetRadius(void);			//получить радиус
	Rect FitRect(void);				//вписать КРУГ в прямоугольник

	//перегруженные методы из Point
	void Show(void);				//показать КРУГ
	void Hide(void);				//скрыть КРУГ
	void Resize(double Scale);		//изменить размер КРУГА

};//end class Circle

/*--------------------------- Класс ТРЕУГОЛЬНИК ------------------------*/
class Triangle : public Point {
private:
	int O;							//основание
	int H;							//высота
public:
	Triangle						//конструктор
		(int InitX = 10, int InitY = 10, 
		 int InitO = 10, int InitH = 10,
		 Color InitClr = { 0, 0, 0 });
	~Triangle(void) {};				//деструктор
	Rect FitRect(void);				//вписать ТРУГОЛЬНИК в прямоугольник

	//перегруженные методы из Point
	void Show(void);				//показать ТРЕУГОЛЬНИК
	void Hide(void);				//скрыть ТРЕУГОЛЬНИК
	void Resize(double Scale);		//изменить размер ТРЕУГОЛЬНИКА

};//end class Triangle

/*---------------------------- Интерфейс ДОМ ---------------------------*/
class IHouse {
public:
	IHouse(void) {};				//конструктор
	virtual ~IHouse(void) {};		//деструктор
	virtual int GetWidth(void) = 0;	//получить ширину
	virtual int GetHeight(void) = 0;//получить высоту
	virtual bool Bump(Rect Obj) = 0;//проверить столкновение с объектом

	/*---------------------отрисовка элементов дома---------------------*/
	virtual void Roof(bool mode) = 0;//крыша
	virtual void Wall(bool mode) = 0;//фасад и фундамент
	virtual void Chimney(bool mode) = 0;//труба
	virtual void Window(void) = 0;	//окно
	virtual void Door(void) = 0;	//дверь
	/*------------------------------------------------------------------*/

};//end class IHouse

/*------------------------------ Класс  ДОМ ----------------------------*/
class House : public Point, public IHouse {
protected:
	int Width;						//ширина
	int Height;						//высота
public:
	House(void);					//конструктор
	~House(void) {};				//деструктор
	int GetWidth(void);				//получить ширину
	int GetHeight(void);			//получить высоту
	bool Bump(Rect Obj);			//проверить столкновение с объектом

	/*---------------------отрисовка элементов дома---------------------*/
	virtual void Roof(bool mode);	//крыша
	virtual void Wall(bool mode);	//фасад и фундамент
	virtual void Chimney(bool mode);//труба
	virtual void Window(void);		//окно
	virtual void Door(void);		//дверь
	/*------------------------------------------------------------------*/

	//перегруженные методы из Point
	void Show(void);				//показать ДОМ
	void Hide(void);				//скрыть ДОМ
	void Resize(double Scale);		//изменить размер ДОМА

};//end class House

/*-------------------------- Класс ПОМЯТЫЙ ДОМ -------------------------*/
class RumpledHouse : public House {
public:
	RumpledHouse(void) : House() {};//конструктор
	~RumpledHouse(void) {};			//деструктор

	/*---------------------отрисовка элементов дома---------------------*/
	virtual void Wall(bool mode);	//фасад и фундамент
	virtual void Chimney(bool mode) {};//труба
	virtual void Window(void);		//окно
	virtual void Door(void);		//дверь
	/*------------------------------------------------------------------*/

};//end class RumpledHouse

/*-------------------------- Класс БЕДНЫЙ ДОМ --------------------------*/
class PoorHouse : public House {
public:
	PoorHouse(void) : House() {};	//конструктор
	~PoorHouse(void) {};			//деструктор

	/*---------------------отрисовка элементов дома---------------------*/
	virtual void Wall(bool mode);	//фасад и фундамент
	virtual void Chimney(bool mode);//труба
	virtual void Window(void);		//окно
	virtual void Door(void);		//дверь
	/*------------------------------------------------------------------*/

};//end class PoorHouse

/*------------------------- Класс БОГАТЫЙ ДОМ --------------------------*/
class RichHouse : public House {
public:
	RichHouse(void) : House() {};	//конструктор
	~RichHouse(void) {};			//деструктор

};//end class RichHouse

/*------------------------ Класс ВОЛШЕБНЫЙ ДОМ -------------------------*/
class MagicHouse : public RichHouse {
public:
	MagicHouse(void) : RichHouse() {};//конструктор
	~MagicHouse(void) {};			//деструктор

	/*---------------------отрисовка элементов дома---------------------*/
	virtual void Roof(bool mode) {};//крыша
	virtual void Chimney(bool mode) {};//труба
	/*------------------------------------------------------------------*/

};//end class MagicHouse

/*------------------------------ Класс ШАР -----------------------------*/
class Ball : public Circle {
protected:
	int Energy;						//количество энергии
public:
	Ball							//конструктор
	(int InitX = 10, int InitY = 10, 
		Color InitClr = { 0, 0, 0 }, int InitEnergy = 0);
	~Ball(void) {};					//деструктор
	int GetEnergy(void);			//получить количество энергии

};//end class Ball

/*-------------------------- Класс ПЛОХОЙ ШАР --------------------------*/
class BadBall : public Ball {
public:
	BadBall							//конструктор
	(int InitX = 10, int InitY = 10) 
		: Ball(InitX, InitY, { 255, 0, 0 }, -1) {};
	~BadBall(void) {};				//деструктор

};//end class BadBall

/*-------------------------- Класс ХОРОШИЙ ШАР -------------------------*/
class GoodBall : public Ball {
public:
	GoodBall						//конструктор
	(int InitX = 10, int InitY = 10)
		: Ball(InitX, InitY, { 0, 255, 0 }, 1) {};
	~GoodBall(void) {};				//деструктор

};//end class GoodBall

/*------------------------ Класс МАГИЧЕСКИЙ ШАР ------------------------*/
class MagicBall : public Ball {
public:
	MagicBall						//конструктор
	(int InitX = 10, int InitY = 10)
		: Ball(InitX, InitY, { 255, 0, 255 }, 2) {};
	~MagicBall(void) {};			//деструктор

};//end class MagicBall

/*----------------------------------------------------------------------*/
/*                  П Р О Т О Т И П Ы    Ф У Н К Ц И Й                  */
/*----------------------------------------------------------------------*/

bool BetweenCoords	(int Check, int A, int B);
int Drag			(House* Active, Ball** Balls, int BallAmount, int Speed);
int RandomInteger	(int From, int To, int mode = 0);

/***********************   End of File CLASSES.H   **********************/