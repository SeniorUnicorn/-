#include <windows.h>
#include <conio.h>
#include <math.h>
#include <sstream>
#include <string>
#include<ctime>

#ifdef UNICODE
typedef std::wostringstream tstringstream;
#else
typedef std::ostringstream tstringstream;
#endif

#include "Classes.h"				//объявление классов
#include "GetConlWin.h"				//указатель на консольное окно

//макрос для проверки состояния клавиатуры – из ШАБЛОНА
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/************************************************************************/
/*  Г Л О Б А Л Ь Н Ы Е    П Е Р Е М Е Н Н Ы Е   И   К О Н С Т А Н Т Ы  */
/************************************************************************/

extern HDC hdc;						//контекст устройства
Color BackGround = { 255, 255, 255 };//цвет фона


/************************************************************************/
/*                 Р Е А Л И З А Ц И Я   М Е Т О Д О В                  */
/************************************************************************/

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Color             */
/*----------------------------------------*/
//конструктор
Color::Color(
	int InitRed,					//красная составляющая цвета
	int InitGreen,					//зеленая составляющая цвета
	int InitBlue) {					//синяя составляющая цвета
	
	//инициализация закрытых полей этого класса
	Red = InitRed;
	Green = InitGreen;
	Blue = InitBlue;

}//end Color::Color()

//получить красную составляющую цвета
int Color::GetRed(void) {
	return Red;

}//end Color::GetRed()

//получить зеленую составляющую цвета
int Color::GetGreen(void) {
	return Green;

}//end Color::GetGreen()

//получить синюю составляющую цвета
int Color::GetBlue(void) {
	return Blue;

}//end Color::GetBlue()

//настроить цвет
void Color::SetColor(
	int NewRed,						//новая красная составляющая цвета 
	int NewGreen,					//новая зеленая составляющая цвета  
	int NewBlue) {					//новая синяя составляющая цвета 
	
	//установка значений нового цвета
	Red = NewRed;
	Green = NewGreen;
	Blue = NewBlue;

}//end Color::SetColor()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Location          */
/*----------------------------------------*/
//конструктор
Location::Location(
	int InitX,						//координата X
	int InitY) {					//координата Y
	
	//инициализация закрытых полей этого класса
	X = InitX;
	Y = InitY;

}//end Location::Location()

//получить координату X
int Location::GetX(void) {
	return X;

}//end Location::GetX()	

//получить координату Y
int Location::GetY(void) {
	return Y;

} //end Location::GetY()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Point             */
/*----------------------------------------*/
//конструктор
Point::Point(
	int InitX,						//координата X 
	int InitY, 						//координата Y
	Color InitClr) :				//цвет
	Location(InitX, InitY) {
	
	//инициализация закрытых полей этого класса
	Clr = InitClr;
	Visible = true;					//сделать фигуру невидимой

}//end Point::Point()

//получить светимость
bool Point::IsVisible(void){
	return Visible;

}//end Point::IsVisible()

//переместить фигуру
void Point::MoveTo(
	int NewX,						//новая координата X
	int NewY){						//новая координата Y
	
	Hide();							//скрыть фигуру
	//обновление координат
	X = NewX;
	Y = NewY;
	Show();							//показать фигуру на новом месте

}//end Point::MoveTo()

//показать фигуру
void Point::Show(void){
	Visible = true;					//сделать фигуру видимой
	
	//нарисовать ТОЧКУ
	SetPixel(hdc, X, Y, RGB(Clr.GetRed(), Clr.GetGreen(), Clr.GetBlue()));

}//end Point::Show()

//скрыть фигуру
void Point::Hide(void){
	Visible = false;				//сделать фигуру невидимой
	
	//нарисовать ТОЧКУ цветом фона
	SetPixel(hdc, X, Y, RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));

}//end Point::Hide()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Rect              */
/*----------------------------------------*/
//конструктор
Rect::Rect(
	int InitX,						//координата X левого верхнего угла
	int InitY, 						//координата Y левого верхнего угла
	int InitA,						//горизонтальная сторона
	int InitB,						//вертикальная сторона
	Color InitClr) :				//цвет
	Point(InitX, InitY, InitClr) {
	
	//инициализация закрытых полей этого класса
	A = InitA;
	B = InitB;

}//end Rect::Rect()

//получить горизонтальную сторону
int Rect::GetA(void){
	return A;

}//end Rect::GetA()

//получить вертикальную сторону
int Rect::GetB(void) {
	return B;

}//end Rect::~Rect()

//вписать ПРЯМОУГОЛЬНИК в прямоугольник
Rect Rect::FitRect(void) {
	return *this;

}//end Rect::FitCircle()

//показать ПРЯМОУГОЛЬНИК
void Rect::Show(void) {
	Visible = true;					//сделать фигуру видимой

	//инициализация кисти и пера
	HBRUSH Brush = CreateSolidBrush(RGB(Clr.GetRed(), 
		Clr.GetGreen(), Clr.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hdc, Brush);		//сделать кисть активной
	//нарисовать ПРЯМОУГОЛЬНИК кистью
	Rectangle(hdc, X, Y, X + A, Y + B);

	SelectObject(hdc, Pen);			//сделать перо активным
	//нарисовать контур ПРЯМОУГОЛЬНИКА пером
	Rectangle(hdc, X, Y, X + A, Y + B);

	//освободить память
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Rect::Show()

//скрыть ПРЯМОУГОЛЬНИК
void Rect::Hide(void) {
	Visible = false;				//сделать фигуру невидимой

	//инициализация кисти и пера
	HBRUSH Brush = CreateSolidBrush(RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));

	SelectObject(hdc, Brush);		//сделать кисть активной
	//нарисовать ПРЯМОУГОЛЬНИК кистью цвета фона
	Rectangle(hdc, X, Y, X + A, Y + B);

	SelectObject(hdc, Pen);			//сделать перо активным
	//нарисовать контур ПРЯМОУГОЛЬНИКА пером цвета фона
	Rectangle(hdc, X, Y, X + A, Y + B);

	//освободить память
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Rect::Hide()

//изменить размер ПРЯМОУГОЛЬНИКА
void Rect::Resize(
	double Scale){					//масштаб
	
	//выровнять координаты фигуры
	MoveTo(X - A * (Scale - 1) / 2, Y - B * (Scale - 1) / 2);
	Hide();							//скрыть фигуру старого размера
	//изменить размер
	A *= Scale;
	B *= Scale;
	Show();							//показать фигуру нового размера

}//end Rect::Resize()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Circle            */
/*----------------------------------------*/
//конструктор
Circle::Circle(
	int InitX,						//координата X центра круга
	int InitY, 						//координата Y центра круга
	int InitRadius,					//радиус
	Color InitClr) :				//цвет
	Point(InitX, InitY, InitClr) {
	
	//инициализация закрытых полей этого класса
	Radius = InitRadius;

}//end Circle::Circle()

//получить радиус
int Circle::GetRadius(void) {
	return Radius;

}//end Circle::GetRadius()

//вписать КРУГ в прямоугольник
Rect Circle::FitRect(void) {
	Rect res(X - Radius, Y - Radius, Radius * 2, Radius * 2, Clr);
	return res;

}//end Circle::FitCircle()

//показать КРУГ
void Circle::Show(void) {
	Visible = true;					//сделать фигуру видимой

	//инициализация кисти и пера
	HBRUSH Brush = CreateSolidBrush(RGB(Clr.GetRed(), 
		Clr.GetGreen(), Clr.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		
	SelectObject(hdc, Brush);		//сделать кисть активной
	//нарисовать КРУГ кистью
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);

	SelectObject(hdc, Pen);			//сделать перо активным
	//нарисовать контур КРУГА пером
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);

	//освободить память
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Circle::Show()

//скрыть КРУГ
void Circle::Hide(void) {
	Visible = false;				//сделать фигуру невидимой

	//инициализация кисти и пера
	HBRUSH Brush = ::CreateSolidBrush(RGB(BackGround.GetRed(),
		BackGround.GetGreen(), BackGround.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(BackGround.GetRed(),
		BackGround.GetGreen(), BackGround.GetBlue()));

	SelectObject(hdc, Brush);		//сделать кисть активной
	//нарисовать КРУГ кистью цвета фона
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);
	
	SelectObject(hdc, Pen);			//сделать перо активным
	//нарисовать контур КРУГА пером цвета фона
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);

	//освободить память
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Circle::Hide()

//изменить размер КРУГА
void Circle::Resize(
	double Scale) {					//масштаб
	
	Hide();							//скрыть фигуру старого размера
	Radius *= Scale;				//изменить размер 
	Show();							//показать фигуру нового размера

}//end Circle::Resize()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Triangle          */
/*----------------------------------------*/
//конструктор
Triangle::Triangle(
	int InitX,						//координата X точки пересечения О и Н
	int InitY, 						//координата Y точки пересечения О и Н
	int InitO,						//основание
	int InitH,						//высота
	Color InitClr) :				//цвет
	Point(InitX, InitY, InitClr) {
	
	//инициализация закрытых полей этого класса
	O = InitO;
	H = InitH;

}//end Triangle::Triangle()

//вписать ТРЕУГОЛЬНИК в прямоугольник
Rect Triangle::FitRect(void) {
	Rect res(X+O/2, Y+H, O, H, Clr);
	return res;

}//end Triangle::FitCircle()

//показать ТРЕУГОЛЬНИК
void Triangle::Show(void) {
	//массив координат вершин треугольника
	POINT dots[3] = { {X, Y - H}, {X + O / 2, Y}, {X - O / 2, Y} };
	Visible = true;					//сделать фигуру видимой

	//инициализация кисти и пера
	HBRUSH Brush = CreateSolidBrush(RGB(Clr.GetRed(), 
		Clr.GetGreen(), Clr.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hdc, Brush);		//сделать кисть активной
	//нарисовать ТРЕУГОЛЬНИК кистью
	Polygon(hdc, dots, 3);

	SelectObject(hdc, Pen);			//сделать перо активным
	//нарисовать контур ТРЕУГОЛЬНИКА пером
	Polygon(hdc, dots, 3);

	//освободить память
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Triangle::Show()

//скрыть ТРЕУГОЛЬНИК
void Triangle::Hide(void) {
	//массив координат вершин треугольника
	POINT dots[3] = { {X, Y - H}, {X + O / 2, Y}, {X - O / 2, Y} };
	Visible = false;				//сделать фигуру невидимой

	//инициализация кисти и пера
	HBRUSH Brush = CreateSolidBrush(RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(BackGround.GetRed(),
		BackGround.GetGreen(), BackGround.GetBlue()));

	SelectObject(hdc, Brush);		//сделать кисть активной
	//нарисовать ТРЕУГОЛЬНИК кистью цвета фона
	Polygon(hdc, dots, 3);

	SelectObject(hdc, Pen);			//сделать перо активным
	//нарисовать контур ТРЕУГОЛЬНИКА пером цвета фона
	Polygon(hdc, dots, 3);

	//освободить память
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Triangle::Hide()

//изменить размер ТРЕУГОЛЬНИКА
void Triangle::Resize(
	double Scale) {					//масштаб
	
	//выровнять координаты фигуры
	MoveTo(X, Y + H * (Scale - 1) / 2);
	Hide();							//скрыть фигуру старого размера
	//изменить размер
	O *= Scale;
	H *= Scale;
	Show();							//показать фигуру нового размера

}//end Triangle::Resize()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА House             */
/*----------------------------------------*/
//конструктор
House::House(void) : Point(100, 100) {

	//инициализация закрытых полей этого класса
	Width = 150;
	Height = 150;

}//end House::House()

//получить ширину
int House::GetWidth(void) {
	return Width;

}//end House::GetWidth()

//получить высоту
int House::GetHeight(void) {
	return Height;

}//end House::GetHeight()

//проверить столкновение с объектом
bool House::Bump(
	Rect Obj) {						//объект для проверки

	//левый верхний угол дома в объекте
	if ((BetweenCoords(X, Obj.GetX(), Obj.GetX() + Obj.GetA())) &&
		(BetweenCoords(Y, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//правый верхний угол дома в объекте
	if ((BetweenCoords(X + Width, Obj.GetX(), Obj.GetX() + Obj.GetA())) &&
		(BetweenCoords(Y, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//левый нижний угол дома в объекте
	if ((BetweenCoords(X, Obj.GetX(), Obj.GetX() + Obj.GetA()))	&&
		(BetweenCoords(Y + Height, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//правый нижний угол дома в объекте
	if ((BetweenCoords(X + Width, Obj.GetX(), Obj.GetX() + Obj.GetA())) &&
		(BetweenCoords(Y + Height, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//левый верхний угол объекта в доме
	if ((BetweenCoords(Obj.GetX(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY(), Y, Y + Height))) {
		return true;
	}//end if

	//правый верхний угол объекта в доме
	if ((BetweenCoords(Obj.GetX() + Obj.GetA(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY(), Y, Y + Height))) {
		return true;
	}//end if

	//левый нижний угол объекта в доме
	if ((BetweenCoords(Obj.GetX(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY() + Obj.GetB(), Y, Y + Height))) {
		return true;
	}//end if

	//правый нижний угол объекта в доме
	if ((BetweenCoords(Obj.GetX() + Obj.GetA(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY() + Obj.GetB(), Y, Y + Height))) {
		return true;
	}//end if

	return false;					//объекты не пересекаются

}//end House::Bump()

/*---------------------- отрисовка элементов дома ----------------------*/
//крыша
void House::Roof(
	bool mode) {					//режим (1 - показать, 0 - скрыть)
	Color Clr;						//цвет

	//выбор цвета
	mode ? Clr.SetColor(107, 15, 15)//бордовый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	Triangle Roof(X + 0.5 * Width, Y + 0.45 * Height,
		0.99 * Width, 0.45 * Height, Clr);
	mode ? Roof.Show()				//показать
		 : Roof.Hide();				//скрыть

}//end House::Roof()

//фасад и фундамент
void House::Wall(
	bool mode) {					//режим (1 - показать, 0 - скрыть)
	Color Clr;						//цвет
	
	//выбор цвета
	mode ? Clr.SetColor(128, 128, 128)//серый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	//фундамент
	Rect Base(X, Y + 0.9 * Height, 0.99 * Width, 0.1 * Height, Clr);
	mode ? Base.Show()				//показать
		 : Base.Hide();				//скрыть

	//выбор цвета
	mode ? Clr.SetColor(230, 216, 151)//бежевый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	//фасад
	Rect Wall(X + 0.05 * Width, Y + 0.45 * Height, 
		0.9 * Width, 0.5 * Height, Clr);
	mode ? Wall.Show()				//показать
		 : Wall.Hide();				//скрыть

}//end House::Wall()

//труба
void House::Chimney(
	bool mode) {					//режим (1 - показать, 0 - скрыть)
	Color Clr;						//цвет

	//выбор цвета
	mode ? Clr.SetColor(128, 128, 128)//серый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	//труба
	Rect Chimney(X + 0.75 * Width, Y + 0.1 * Height, 
		0.15 * Width, 0.3 * Height, Clr);
	mode ? Chimney.Show()			//показать
		 : Chimney.Hide();			//скрыть

	//верх трубы
	Rect ChimneyTop(X + 0.7 * Width, Y + 0.06 * Height,
		0.25 * Width, 0.05 * Height, Clr);
	mode ? ChimneyTop.Show()		//показать
		 : ChimneyTop.Hide();		//скрыть

}//end House::Chimney()

//окно
void House::Window(void) {
	Color Clr;						//цвет
	Clr.SetColor(97, 70, 51);		//коричневый цвет

	//рама окна
	Rect Window(X + 0.5 * Width, Y + 0.55 * Height,
		0.36 * Width, 0.3 * Height, Clr);
	Window.Show();					//показать

	//подоконник
	Rect Sill(X + 0.45 * Width, Y + 0.84 * Height,
		0.45 * Width, 0.03 * Height, Clr);
	Sill.Show();					//показать

	Clr.SetColor(167, 224, 252);	//голубой цвет

	//стёкла окна
	Rect WindowGlass1(X + 0.52 * Width, Y + 0.57 * Height,
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass1.Show();			//показать
	Rect WindowGlass2(X + 0.69 * Width, Y + 0.57 * Height, 
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass2.Show();			//показать
	Rect WindowGlass3(X + 0.52 * Width, Y + 0.71 * Height, 
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass3.Show();			//показать
	Rect WindowGlass4(X + 0.69 * Width, Y + 0.71 * Height, 
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass4.Show();			//показать

}//end House::Window()

//дверь
void House::Door(void) {
	Color Clr;						//цвет
	Clr.SetColor(97, 70, 51);		//коричневый цвет

	//дверь
	Rect Door(X + 0.15 * Width, Y + 0.54 * Height,
		0.26 * Width, 0.4 * Height, Clr);
	Door.Show();					//показать

	Clr.SetColor(167, 224, 252);	//голубой цвет

	//стёкла двери
	Rect DoorGlass1(X + 0.17 * Width, Y + 0.57 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass1.Show();				//показать
	Rect DoorGlass2(X + 0.29 * Width, Y + 0.57 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass2.Show();				//показать
	Rect DoorGlass3(X + 0.17 * Width, Y + 0.67 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass3.Show();				//показать
	Rect DoorGlass4(X + 0.29 * Width, Y + 0.67 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass4.Show();				//показать

}//end House::Door()
/*----------------------------------------------------------------------*/

//показать ДОМ
void House::Show(void) {
	Visible = true;					//сделать фигуру видимой

	Wall(Visible);					//показать фасад и фундамент
	Chimney(Visible);				//показать трубу
	Roof(Visible);					//показать крышу
	Door();							//показать дверь
	Window();						//показать окно

}//end House::Show()

//скрыть ДОМ
void House::Hide(void) {
	Visible = false;				//сделать фигуру невидимой

	Wall(Visible);					//скрыть фасад и фундамент
	Chimney(Visible);				//скрыть трубу
	Roof(Visible);					//скрыть крышу

}//end House::Hide()

//изменить размер ДОМА
void House::Resize(
	double Scale) {					//масштаб
	
	//выровнять координаты фигуры
	MoveTo(X - Width * (Scale - 1) / 2, Y - Height * (Scale - 1) / 2);
	Hide();							//скрыть фигуру старого размера
	//изменить размер
	Width *= Scale;
	Height *= Scale;
	Show();							//показать фигуру нового размера

}//end House::Resize()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА RumpledHouse             */
/*-----------------------------------------------*/
//отрисовка фасада и фундамента
void RumpledHouse::Wall(
	bool mode) {					//режим (1 - показать, 0 - скрыть)
	Color Clr;						//цвет

	//выбор цвета
	mode ? Clr.SetColor(230, 216, 151)//бежевый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	//фасад
	Rect Wall(X + 0.05 * Width, Y + 0.45 * Height,
		0.9 * Width, 0.5 * Height, Clr);
	mode ? Wall.Show()				//показать
		: Wall.Hide();				//скрыть

}//end RumpledHouse::Wall()

//отрисовка окна
void RumpledHouse::Window(void) {
	Color Clr;						//цвет
	Clr.SetColor(0, 0, 0);			//черный цвет

	//окно
	Rect WindowGlass1(X + 0.52 * Width, Y + 0.57 * Height, 
		0.32 * Width, 0.26 * Height, Clr);
	WindowGlass1.Show();			//показать

}//end RumpledHouse::Window()

//отрисовка двери
void RumpledHouse::Door(void) {
	Color Clr;						//цвет
	Clr.SetColor(97, 70, 51);		//коричневый цвет

	//дверь
	Rect Door(X + 0.15 * Width, Y + 0.54 * Height, 
		0.26 * Width, 0.4 * Height, Clr);
	Door.Show();					//показать

	Clr.SetColor(0, 0, 0);			//черный цвет

	//стекло двери
	Rect DoorGlass(X + 0.17 * Width, Y + 0.57 * Height,
		0.22 * Width, 0.18 * Height, Clr);
	DoorGlass.Show();				//показать

}//end RumpledHouse::Door()

/*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА PoorHouse             */
/*--------------------------------------------*/
//отрисовка фасада и фундамента
void PoorHouse::Wall(
	bool mode) {					//режим (1 - показать, 0 - скрыть)
	Color Clr;						//цвет

	//выбор цвета
	mode ? Clr.SetColor(230, 216, 151)//бежевый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	//фасад
	Rect Wall(X + 0.05 * Width, Y + 0.45 * Height, 0.9 * Width, 0.5 * Height, Clr);
	mode ? Wall.Show()				//показать
		 : Wall.Hide();				//скрыть

}//end PoorHouse::Wall()

//отрисовка трубы
void PoorHouse::Chimney(
	bool mode) {					//режим (1 - показать, 0 - скрыть)
	Color Clr;						//цвет
	mode ? Clr.SetColor(128, 128, 128)//серый цвет
		 : Clr.SetColor(255, 255, 255);//цвет фона

	//труба
	Rect Chimney(X + 0.75 * Width, Y + 0.1 * Height, 0.15 * Width, 0.3 * Height, Clr);
	mode ? Chimney.Show()			//показать
		 : Chimney.Hide();			//скрыть

}//end PoorHouse::Chimney()

//отрисовка окна
void PoorHouse::Window(void) {
	Color Clr;						//цвет
	Clr.SetColor(97, 70, 51);		//коричневый цвет

	//рама окна
	Rect Window(X + 0.5 * Width, Y + 0.55 * Height,
		0.36 * Width, 0.3 * Height, Clr);
	Window.Show();					//показать

	Clr.SetColor(167, 224, 252);	//голубой цвет

	//стекло окна
	Rect WindowGlass(X + 0.52 * Width, Y + 0.57 * Height, 
		0.32 * Width, 0.26 * Height, Clr);
	WindowGlass.Show();				//показать

}//end PoorHouse::Window()

//отрисовка двери
void PoorHouse::Door(void) {
	Color Clr;						//цвет
	Clr.SetColor(97, 70, 51);		//коричневый цвет

	//дверь
	Rect Door(X + 0.15 * Width, Y + 0.54 * Height, 
		0.26 * Width, 0.4 * Height, Clr);
	Door.Show();					//показать

	Clr.SetColor(167, 224, 252);	//голубой цвет

	//стекло двери
	Rect DoorGlass(X + 0.17 * Width, Y + 0.57 * Height, 
		0.22 * Width, 0.18 * Height, Clr);
	DoorGlass.Show();				//показать

}//end PoorHouse::Door()

 /*----------------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Ball              */
/*----------------------------------------*/
//конструктор
Ball::Ball(
	int InitX,						//координата X точки центра шара
	int InitY, 						//координата Y точки центра шара
	Color InitClr,					//цвет
	int InitEnergy) :				//энергия
	Circle(InitX, InitY, 30, InitClr) {

	//инициализация закрытых полей этого класса
	Energy = InitEnergy;

}//end Ball::Ball()

//получить количество энергии
int Ball::GetEnergy(void) {
	return Energy;

}//end Ball::GetEnergy()

/************************************************************************/
/*                 Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й                  */
/************************************************************************/
/*----------------------------------------------------------------------*/
/*   Проверка нахождения числа в отрезке   */
/*-----------------------------------------*/
bool BetweenCoords(
	int Check,						//число
	int A,							//нижняя граница отрезка
	int B) {						//верхняя граница отрезка
	if (((Check >= B) && (Check <= A)) ||//число в отрезке [B; A]
		((Check >= A) && (Check <= B))) {//число в отрезке [A; B]
		return true;
	}//end if

	return false;					//число не в отрезке

}//end BetweenCoords()

/*----------------------------------------------------------------------*/
/*   Буксировка фигуры и обработка столкновений   */
/*------------------------------------------------*/
int Drag(
	House* Active,					//активная фигура
	Ball** Balls,					//массив препятствий
	int BallAmount,					//количество препятствий
	int Speed) {					//скорость движения
	int FigX, FigY;					//новые координаты фигуры
	
	//начальное положение фигуры
	FigX = Active->GetX();
	FigY = Active->GetY();

	while (1) {						//бесконечный цикл буксировки
		while (KEY_DOWN(VK_LEFT)) {	//стрелка влево  37
			FigX -= Speed;			//приращение координаты
			//перемещение активной фигуры
			Active->MoveTo(FigX, FigY);
			//поиск столкновения
			for (int i = 0; i < BallAmount; i++) {
				//столкновение обнаружено
				if (Active->Bump(Balls[i]->FitRect())) {
					FigX += Speed;	//обратное приращение координаты
					//перемещение активной фигуры
					Active->MoveTo(FigX, FigY);
					return i;		//вернуть индекс препятствия
				}//end if
			}//end for i
			Sleep(50);				//пауза
		}//end while

		while (KEY_DOWN(VK_RIGHT)) {	//стрелка вправо  39
			FigX += Speed;			//приращение координаты
			//перемещение активной фигуры
			Active->MoveTo(FigX, FigY);
			//поиск столкновения
			for (int i = 0; i < BallAmount; i++) {
				//столкновение обнаружено
				if (Active->Bump(Balls[i]->FitRect())) {
					FigX -= Speed;	//обратное приращение координаты
					//перемещение активной фигуры
					Active->MoveTo(FigX, FigY);
					return i;		//вернуть индекс препятствия
				}//end if
			}//end for i
			Sleep(50);				//пауза
		}//end while

		while (KEY_DOWN(VK_DOWN)) {	//стрелка вниз  40
			FigY += Speed;			//приращение координаты
			//перемещение активной фигуры
			Active->MoveTo(FigX, FigY);
			//поиск столкновения
			for (int i = 0; i < BallAmount; i++) {
				//столкновение обнаружено
				if (Active->Bump(Balls[i]->FitRect())) {
					FigY -= Speed;	//обратное приращение координаты
					//перемещение активной фигуры
					Active->MoveTo(FigX, FigY);
					return i;		//вернуть индекс препятствия
				}//end if
			}//end for i
			Sleep(50);				//пауза
		}//end while

		while (KEY_DOWN(VK_UP)) {	//стрелка вверх  38
			FigY -= Speed;			//приращение координаты
			//перемещение активной фигуры
			Active->MoveTo(FigX, FigY);
			//поиск столкновения
			for (int i = 0; i < BallAmount; i++) {
				//столкновение обнаружено
				if (Active->Bump(Balls[i]->FitRect())) {
					FigY += Speed;	//обратное приращение координаты
					//перемещение активной фигуры
					Active->MoveTo(FigX, FigY);
					return i;		//вернуть индекс препятствия
				}//end if
			}//end for i
			Sleep(50);				//пауза
		}//end while

		if (KEY_DOWN(VK_ESCAPE)) {	//выход из игры по кнопке Esc
			return -1;
		}//end if
	}//end while

}//end Drag()

/*----------------------------------------------------------------------*/
/*   Случайное число из интервала   */
/*----------------------------------*/
int RandomInteger(
	int From,						//нижняя граница интервала
	int To,							//верхняя граница интервала
	int mode) {						//режим (1 - фиксированный знак,
									//0 - переменный(по умолчанию)
	//расчет числа в интервале
	int randDigit = rand() % (abs(To - From)) + From;

	//расчет знака
	double randSign = (rand() % 20) - 10;
	if ((randSign > 0) || (mode == 1)) {//знак + или режим без знака
		return randDigit;
	} else {						//знак -
		return -randDigit;
	}//end if

}//end RandomInteger()

/**********************   End of File CLASSES.СPP   *********************/