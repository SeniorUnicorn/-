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

#include "Classes.h"				//���������� �������
#include "GetConlWin.h"				//��������� �� ���������� ����

//������ ��� �������� ��������� ���������� � �� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/************************************************************************/
/*  � � � � � � � � � �    � � � � � � � � � �   �   � � � � � � � � �  */
/************************************************************************/

extern HDC hdc;						//�������� ����������
Color BackGround = { 255, 255, 255 };//���� ����


/************************************************************************/
/*                 � � � � � � � � � �   � � � � � � �                  */
/************************************************************************/

/*----------------------------------------------------------------------*/
/*        ������ ������ Color             */
/*----------------------------------------*/
//�����������
Color::Color(
	int InitRed,					//������� ������������ �����
	int InitGreen,					//������� ������������ �����
	int InitBlue) {					//����� ������������ �����
	
	//������������� �������� ����� ����� ������
	Red = InitRed;
	Green = InitGreen;
	Blue = InitBlue;

}//end Color::Color()

//�������� ������� ������������ �����
int Color::GetRed(void) {
	return Red;

}//end Color::GetRed()

//�������� ������� ������������ �����
int Color::GetGreen(void) {
	return Green;

}//end Color::GetGreen()

//�������� ����� ������������ �����
int Color::GetBlue(void) {
	return Blue;

}//end Color::GetBlue()

//��������� ����
void Color::SetColor(
	int NewRed,						//����� ������� ������������ ����� 
	int NewGreen,					//����� ������� ������������ �����  
	int NewBlue) {					//����� ����� ������������ ����� 
	
	//��������� �������� ������ �����
	Red = NewRed;
	Green = NewGreen;
	Blue = NewBlue;

}//end Color::SetColor()

/*----------------------------------------------------------------------*/
/*        ������ ������ Location          */
/*----------------------------------------*/
//�����������
Location::Location(
	int InitX,						//���������� X
	int InitY) {					//���������� Y
	
	//������������� �������� ����� ����� ������
	X = InitX;
	Y = InitY;

}//end Location::Location()

//�������� ���������� X
int Location::GetX(void) {
	return X;

}//end Location::GetX()	

//�������� ���������� Y
int Location::GetY(void) {
	return Y;

} //end Location::GetY()

/*----------------------------------------------------------------------*/
/*        ������ ������ Point             */
/*----------------------------------------*/
//�����������
Point::Point(
	int InitX,						//���������� X 
	int InitY, 						//���������� Y
	Color InitClr) :				//����
	Location(InitX, InitY) {
	
	//������������� �������� ����� ����� ������
	Clr = InitClr;
	Visible = true;					//������� ������ ���������

}//end Point::Point()

//�������� ����������
bool Point::IsVisible(void){
	return Visible;

}//end Point::IsVisible()

//����������� ������
void Point::MoveTo(
	int NewX,						//����� ���������� X
	int NewY){						//����� ���������� Y
	
	Hide();							//������ ������
	//���������� ���������
	X = NewX;
	Y = NewY;
	Show();							//�������� ������ �� ����� �����

}//end Point::MoveTo()

//�������� ������
void Point::Show(void){
	Visible = true;					//������� ������ �������
	
	//���������� �����
	SetPixel(hdc, X, Y, RGB(Clr.GetRed(), Clr.GetGreen(), Clr.GetBlue()));

}//end Point::Show()

//������ ������
void Point::Hide(void){
	Visible = false;				//������� ������ ���������
	
	//���������� ����� ������ ����
	SetPixel(hdc, X, Y, RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));

}//end Point::Hide()

/*----------------------------------------------------------------------*/
/*        ������ ������ Rect              */
/*----------------------------------------*/
//�����������
Rect::Rect(
	int InitX,						//���������� X ������ �������� ����
	int InitY, 						//���������� Y ������ �������� ����
	int InitA,						//�������������� �������
	int InitB,						//������������ �������
	Color InitClr) :				//����
	Point(InitX, InitY, InitClr) {
	
	//������������� �������� ����� ����� ������
	A = InitA;
	B = InitB;

}//end Rect::Rect()

//�������� �������������� �������
int Rect::GetA(void){
	return A;

}//end Rect::GetA()

//�������� ������������ �������
int Rect::GetB(void) {
	return B;

}//end Rect::~Rect()

//������� ������������� � �������������
Rect Rect::FitRect(void) {
	return *this;

}//end Rect::FitCircle()

//�������� �������������
void Rect::Show(void) {
	Visible = true;					//������� ������ �������

	//������������� ����� � ����
	HBRUSH Brush = CreateSolidBrush(RGB(Clr.GetRed(), 
		Clr.GetGreen(), Clr.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hdc, Brush);		//������� ����� ��������
	//���������� ������������� ������
	Rectangle(hdc, X, Y, X + A, Y + B);

	SelectObject(hdc, Pen);			//������� ���� ��������
	//���������� ������ �������������� �����
	Rectangle(hdc, X, Y, X + A, Y + B);

	//���������� ������
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Rect::Show()

//������ �������������
void Rect::Hide(void) {
	Visible = false;				//������� ������ ���������

	//������������� ����� � ����
	HBRUSH Brush = CreateSolidBrush(RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));

	SelectObject(hdc, Brush);		//������� ����� ��������
	//���������� ������������� ������ ����� ����
	Rectangle(hdc, X, Y, X + A, Y + B);

	SelectObject(hdc, Pen);			//������� ���� ��������
	//���������� ������ �������������� ����� ����� ����
	Rectangle(hdc, X, Y, X + A, Y + B);

	//���������� ������
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Rect::Hide()

//�������� ������ ��������������
void Rect::Resize(
	double Scale){					//�������
	
	//��������� ���������� ������
	MoveTo(X - A * (Scale - 1) / 2, Y - B * (Scale - 1) / 2);
	Hide();							//������ ������ ������� �������
	//�������� ������
	A *= Scale;
	B *= Scale;
	Show();							//�������� ������ ������ �������

}//end Rect::Resize()

/*----------------------------------------------------------------------*/
/*        ������ ������ Circle            */
/*----------------------------------------*/
//�����������
Circle::Circle(
	int InitX,						//���������� X ������ �����
	int InitY, 						//���������� Y ������ �����
	int InitRadius,					//������
	Color InitClr) :				//����
	Point(InitX, InitY, InitClr) {
	
	//������������� �������� ����� ����� ������
	Radius = InitRadius;

}//end Circle::Circle()

//�������� ������
int Circle::GetRadius(void) {
	return Radius;

}//end Circle::GetRadius()

//������� ���� � �������������
Rect Circle::FitRect(void) {
	Rect res(X - Radius, Y - Radius, Radius * 2, Radius * 2, Clr);
	return res;

}//end Circle::FitCircle()

//�������� ����
void Circle::Show(void) {
	Visible = true;					//������� ������ �������

	//������������� ����� � ����
	HBRUSH Brush = CreateSolidBrush(RGB(Clr.GetRed(), 
		Clr.GetGreen(), Clr.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		
	SelectObject(hdc, Brush);		//������� ����� ��������
	//���������� ���� ������
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);

	SelectObject(hdc, Pen);			//������� ���� ��������
	//���������� ������ ����� �����
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);

	//���������� ������
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Circle::Show()

//������ ����
void Circle::Hide(void) {
	Visible = false;				//������� ������ ���������

	//������������� ����� � ����
	HBRUSH Brush = ::CreateSolidBrush(RGB(BackGround.GetRed(),
		BackGround.GetGreen(), BackGround.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(BackGround.GetRed(),
		BackGround.GetGreen(), BackGround.GetBlue()));

	SelectObject(hdc, Brush);		//������� ����� ��������
	//���������� ���� ������ ����� ����
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);
	
	SelectObject(hdc, Pen);			//������� ���� ��������
	//���������� ������ ����� ����� ����� ����
	Ellipse(hdc, X - Radius, Y - Radius, X + Radius, Y + Radius);

	//���������� ������
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Circle::Hide()

//�������� ������ �����
void Circle::Resize(
	double Scale) {					//�������
	
	Hide();							//������ ������ ������� �������
	Radius *= Scale;				//�������� ������ 
	Show();							//�������� ������ ������ �������

}//end Circle::Resize()

/*----------------------------------------------------------------------*/
/*        ������ ������ Triangle          */
/*----------------------------------------*/
//�����������
Triangle::Triangle(
	int InitX,						//���������� X ����� ����������� � � �
	int InitY, 						//���������� Y ����� ����������� � � �
	int InitO,						//���������
	int InitH,						//������
	Color InitClr) :				//����
	Point(InitX, InitY, InitClr) {
	
	//������������� �������� ����� ����� ������
	O = InitO;
	H = InitH;

}//end Triangle::Triangle()

//������� ����������� � �������������
Rect Triangle::FitRect(void) {
	Rect res(X+O/2, Y+H, O, H, Clr);
	return res;

}//end Triangle::FitCircle()

//�������� �����������
void Triangle::Show(void) {
	//������ ��������� ������ ������������
	POINT dots[3] = { {X, Y - H}, {X + O / 2, Y}, {X - O / 2, Y} };
	Visible = true;					//������� ������ �������

	//������������� ����� � ����
	HBRUSH Brush = CreateSolidBrush(RGB(Clr.GetRed(), 
		Clr.GetGreen(), Clr.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	SelectObject(hdc, Brush);		//������� ����� ��������
	//���������� ����������� ������
	Polygon(hdc, dots, 3);

	SelectObject(hdc, Pen);			//������� ���� ��������
	//���������� ������ ������������ �����
	Polygon(hdc, dots, 3);

	//���������� ������
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Triangle::Show()

//������ �����������
void Triangle::Hide(void) {
	//������ ��������� ������ ������������
	POINT dots[3] = { {X, Y - H}, {X + O / 2, Y}, {X - O / 2, Y} };
	Visible = false;				//������� ������ ���������

	//������������� ����� � ����
	HBRUSH Brush = CreateSolidBrush(RGB(BackGround.GetRed(), 
		BackGround.GetGreen(), BackGround.GetBlue()));
	HPEN Pen = CreatePen(PS_SOLID, 1, RGB(BackGround.GetRed(),
		BackGround.GetGreen(), BackGround.GetBlue()));

	SelectObject(hdc, Brush);		//������� ����� ��������
	//���������� ����������� ������ ����� ����
	Polygon(hdc, dots, 3);

	SelectObject(hdc, Pen);			//������� ���� ��������
	//���������� ������ ������������ ����� ����� ����
	Polygon(hdc, dots, 3);

	//���������� ������
	DeleteObject(Brush);
	DeleteObject(Pen);

}//end Triangle::Hide()

//�������� ������ ������������
void Triangle::Resize(
	double Scale) {					//�������
	
	//��������� ���������� ������
	MoveTo(X, Y + H * (Scale - 1) / 2);
	Hide();							//������ ������ ������� �������
	//�������� ������
	O *= Scale;
	H *= Scale;
	Show();							//�������� ������ ������ �������

}//end Triangle::Resize()

/*----------------------------------------------------------------------*/
/*        ������ ������ House             */
/*----------------------------------------*/
//�����������
House::House(void) : Point(100, 100) {

	//������������� �������� ����� ����� ������
	Width = 150;
	Height = 150;

}//end House::House()

//�������� ������
int House::GetWidth(void) {
	return Width;

}//end House::GetWidth()

//�������� ������
int House::GetHeight(void) {
	return Height;

}//end House::GetHeight()

//��������� ������������ � ��������
bool House::Bump(
	Rect Obj) {						//������ ��� ��������

	//����� ������� ���� ���� � �������
	if ((BetweenCoords(X, Obj.GetX(), Obj.GetX() + Obj.GetA())) &&
		(BetweenCoords(Y, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//������ ������� ���� ���� � �������
	if ((BetweenCoords(X + Width, Obj.GetX(), Obj.GetX() + Obj.GetA())) &&
		(BetweenCoords(Y, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//����� ������ ���� ���� � �������
	if ((BetweenCoords(X, Obj.GetX(), Obj.GetX() + Obj.GetA()))	&&
		(BetweenCoords(Y + Height, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//������ ������ ���� ���� � �������
	if ((BetweenCoords(X + Width, Obj.GetX(), Obj.GetX() + Obj.GetA())) &&
		(BetweenCoords(Y + Height, Obj.GetY(), Obj.GetY() + Obj.GetB()))) {
		return true;
	}//end if

	//����� ������� ���� ������� � ����
	if ((BetweenCoords(Obj.GetX(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY(), Y, Y + Height))) {
		return true;
	}//end if

	//������ ������� ���� ������� � ����
	if ((BetweenCoords(Obj.GetX() + Obj.GetA(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY(), Y, Y + Height))) {
		return true;
	}//end if

	//����� ������ ���� ������� � ����
	if ((BetweenCoords(Obj.GetX(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY() + Obj.GetB(), Y, Y + Height))) {
		return true;
	}//end if

	//������ ������ ���� ������� � ����
	if ((BetweenCoords(Obj.GetX() + Obj.GetA(), X, X + Width)) &&
		(BetweenCoords(Obj.GetY() + Obj.GetB(), Y, Y + Height))) {
		return true;
	}//end if

	return false;					//������� �� ������������

}//end House::Bump()

/*---------------------- ��������� ��������� ���� ----------------------*/
//�����
void House::Roof(
	bool mode) {					//����� (1 - ��������, 0 - ������)
	Color Clr;						//����

	//����� �����
	mode ? Clr.SetColor(107, 15, 15)//�������� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	Triangle Roof(X + 0.5 * Width, Y + 0.45 * Height,
		0.99 * Width, 0.45 * Height, Clr);
	mode ? Roof.Show()				//��������
		 : Roof.Hide();				//������

}//end House::Roof()

//����� � ���������
void House::Wall(
	bool mode) {					//����� (1 - ��������, 0 - ������)
	Color Clr;						//����
	
	//����� �����
	mode ? Clr.SetColor(128, 128, 128)//����� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	//���������
	Rect Base(X, Y + 0.9 * Height, 0.99 * Width, 0.1 * Height, Clr);
	mode ? Base.Show()				//��������
		 : Base.Hide();				//������

	//����� �����
	mode ? Clr.SetColor(230, 216, 151)//������� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	//�����
	Rect Wall(X + 0.05 * Width, Y + 0.45 * Height, 
		0.9 * Width, 0.5 * Height, Clr);
	mode ? Wall.Show()				//��������
		 : Wall.Hide();				//������

}//end House::Wall()

//�����
void House::Chimney(
	bool mode) {					//����� (1 - ��������, 0 - ������)
	Color Clr;						//����

	//����� �����
	mode ? Clr.SetColor(128, 128, 128)//����� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	//�����
	Rect Chimney(X + 0.75 * Width, Y + 0.1 * Height, 
		0.15 * Width, 0.3 * Height, Clr);
	mode ? Chimney.Show()			//��������
		 : Chimney.Hide();			//������

	//���� �����
	Rect ChimneyTop(X + 0.7 * Width, Y + 0.06 * Height,
		0.25 * Width, 0.05 * Height, Clr);
	mode ? ChimneyTop.Show()		//��������
		 : ChimneyTop.Hide();		//������

}//end House::Chimney()

//����
void House::Window(void) {
	Color Clr;						//����
	Clr.SetColor(97, 70, 51);		//���������� ����

	//���� ����
	Rect Window(X + 0.5 * Width, Y + 0.55 * Height,
		0.36 * Width, 0.3 * Height, Clr);
	Window.Show();					//��������

	//����������
	Rect Sill(X + 0.45 * Width, Y + 0.84 * Height,
		0.45 * Width, 0.03 * Height, Clr);
	Sill.Show();					//��������

	Clr.SetColor(167, 224, 252);	//������� ����

	//����� ����
	Rect WindowGlass1(X + 0.52 * Width, Y + 0.57 * Height,
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass1.Show();			//��������
	Rect WindowGlass2(X + 0.69 * Width, Y + 0.57 * Height, 
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass2.Show();			//��������
	Rect WindowGlass3(X + 0.52 * Width, Y + 0.71 * Height, 
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass3.Show();			//��������
	Rect WindowGlass4(X + 0.69 * Width, Y + 0.71 * Height, 
		0.15 * Width, 0.12 * Height, Clr);
	WindowGlass4.Show();			//��������

}//end House::Window()

//�����
void House::Door(void) {
	Color Clr;						//����
	Clr.SetColor(97, 70, 51);		//���������� ����

	//�����
	Rect Door(X + 0.15 * Width, Y + 0.54 * Height,
		0.26 * Width, 0.4 * Height, Clr);
	Door.Show();					//��������

	Clr.SetColor(167, 224, 252);	//������� ����

	//����� �����
	Rect DoorGlass1(X + 0.17 * Width, Y + 0.57 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass1.Show();				//��������
	Rect DoorGlass2(X + 0.29 * Width, Y + 0.57 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass2.Show();				//��������
	Rect DoorGlass3(X + 0.17 * Width, Y + 0.67 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass3.Show();				//��������
	Rect DoorGlass4(X + 0.29 * Width, Y + 0.67 * Height,
		0.1 * Width, 0.08 * Height, Clr);
	DoorGlass4.Show();				//��������

}//end House::Door()
/*----------------------------------------------------------------------*/

//�������� ���
void House::Show(void) {
	Visible = true;					//������� ������ �������

	Wall(Visible);					//�������� ����� � ���������
	Chimney(Visible);				//�������� �����
	Roof(Visible);					//�������� �����
	Door();							//�������� �����
	Window();						//�������� ����

}//end House::Show()

//������ ���
void House::Hide(void) {
	Visible = false;				//������� ������ ���������

	Wall(Visible);					//������ ����� � ���������
	Chimney(Visible);				//������ �����
	Roof(Visible);					//������ �����

}//end House::Hide()

//�������� ������ ����
void House::Resize(
	double Scale) {					//�������
	
	//��������� ���������� ������
	MoveTo(X - Width * (Scale - 1) / 2, Y - Height * (Scale - 1) / 2);
	Hide();							//������ ������ ������� �������
	//�������� ������
	Width *= Scale;
	Height *= Scale;
	Show();							//�������� ������ ������ �������

}//end House::Resize()

/*----------------------------------------------------------------------*/
/*        ������ ������ RumpledHouse             */
/*-----------------------------------------------*/
//��������� ������ � ����������
void RumpledHouse::Wall(
	bool mode) {					//����� (1 - ��������, 0 - ������)
	Color Clr;						//����

	//����� �����
	mode ? Clr.SetColor(230, 216, 151)//������� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	//�����
	Rect Wall(X + 0.05 * Width, Y + 0.45 * Height,
		0.9 * Width, 0.5 * Height, Clr);
	mode ? Wall.Show()				//��������
		: Wall.Hide();				//������

}//end RumpledHouse::Wall()

//��������� ����
void RumpledHouse::Window(void) {
	Color Clr;						//����
	Clr.SetColor(0, 0, 0);			//������ ����

	//����
	Rect WindowGlass1(X + 0.52 * Width, Y + 0.57 * Height, 
		0.32 * Width, 0.26 * Height, Clr);
	WindowGlass1.Show();			//��������

}//end RumpledHouse::Window()

//��������� �����
void RumpledHouse::Door(void) {
	Color Clr;						//����
	Clr.SetColor(97, 70, 51);		//���������� ����

	//�����
	Rect Door(X + 0.15 * Width, Y + 0.54 * Height, 
		0.26 * Width, 0.4 * Height, Clr);
	Door.Show();					//��������

	Clr.SetColor(0, 0, 0);			//������ ����

	//������ �����
	Rect DoorGlass(X + 0.17 * Width, Y + 0.57 * Height,
		0.22 * Width, 0.18 * Height, Clr);
	DoorGlass.Show();				//��������

}//end RumpledHouse::Door()

/*----------------------------------------------------------------------*/
/*        ������ ������ PoorHouse             */
/*--------------------------------------------*/
//��������� ������ � ����������
void PoorHouse::Wall(
	bool mode) {					//����� (1 - ��������, 0 - ������)
	Color Clr;						//����

	//����� �����
	mode ? Clr.SetColor(230, 216, 151)//������� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	//�����
	Rect Wall(X + 0.05 * Width, Y + 0.45 * Height, 0.9 * Width, 0.5 * Height, Clr);
	mode ? Wall.Show()				//��������
		 : Wall.Hide();				//������

}//end PoorHouse::Wall()

//��������� �����
void PoorHouse::Chimney(
	bool mode) {					//����� (1 - ��������, 0 - ������)
	Color Clr;						//����
	mode ? Clr.SetColor(128, 128, 128)//����� ����
		 : Clr.SetColor(255, 255, 255);//���� ����

	//�����
	Rect Chimney(X + 0.75 * Width, Y + 0.1 * Height, 0.15 * Width, 0.3 * Height, Clr);
	mode ? Chimney.Show()			//��������
		 : Chimney.Hide();			//������

}//end PoorHouse::Chimney()

//��������� ����
void PoorHouse::Window(void) {
	Color Clr;						//����
	Clr.SetColor(97, 70, 51);		//���������� ����

	//���� ����
	Rect Window(X + 0.5 * Width, Y + 0.55 * Height,
		0.36 * Width, 0.3 * Height, Clr);
	Window.Show();					//��������

	Clr.SetColor(167, 224, 252);	//������� ����

	//������ ����
	Rect WindowGlass(X + 0.52 * Width, Y + 0.57 * Height, 
		0.32 * Width, 0.26 * Height, Clr);
	WindowGlass.Show();				//��������

}//end PoorHouse::Window()

//��������� �����
void PoorHouse::Door(void) {
	Color Clr;						//����
	Clr.SetColor(97, 70, 51);		//���������� ����

	//�����
	Rect Door(X + 0.15 * Width, Y + 0.54 * Height, 
		0.26 * Width, 0.4 * Height, Clr);
	Door.Show();					//��������

	Clr.SetColor(167, 224, 252);	//������� ����

	//������ �����
	Rect DoorGlass(X + 0.17 * Width, Y + 0.57 * Height, 
		0.22 * Width, 0.18 * Height, Clr);
	DoorGlass.Show();				//��������

}//end PoorHouse::Door()

 /*----------------------------------------------------------------------*/
/*        ������ ������ Ball              */
/*----------------------------------------*/
//�����������
Ball::Ball(
	int InitX,						//���������� X ����� ������ ����
	int InitY, 						//���������� Y ����� ������ ����
	Color InitClr,					//����
	int InitEnergy) :				//�������
	Circle(InitX, InitY, 30, InitClr) {

	//������������� �������� ����� ����� ������
	Energy = InitEnergy;

}//end Ball::Ball()

//�������� ���������� �������
int Ball::GetEnergy(void) {
	return Energy;

}//end Ball::GetEnergy()

/************************************************************************/
/*                 � � � � � � � � � �   � � � � � � �                  */
/************************************************************************/
/*----------------------------------------------------------------------*/
/*   �������� ���������� ����� � �������   */
/*-----------------------------------------*/
bool BetweenCoords(
	int Check,						//�����
	int A,							//������ ������� �������
	int B) {						//������� ������� �������
	if (((Check >= B) && (Check <= A)) ||//����� � ������� [B; A]
		((Check >= A) && (Check <= B))) {//����� � ������� [A; B]
		return true;
	}//end if

	return false;					//����� �� � �������

}//end BetweenCoords()

/*----------------------------------------------------------------------*/
/*   ���������� ������ � ��������� ������������   */
/*------------------------------------------------*/
int Drag(
	House* Active,					//�������� ������
	Ball** Balls,					//������ �����������
	int BallAmount,					//���������� �����������
	int Speed) {					//�������� ��������
	int FigX, FigY;					//����� ���������� ������
	
	//��������� ��������� ������
	FigX = Active->GetX();
	FigY = Active->GetY();

	while (1) {						//����������� ���� ����������
		while (KEY_DOWN(VK_LEFT)) {	//������� �����  37
			FigX -= Speed;			//���������� ����������
			//����������� �������� ������
			Active->MoveTo(FigX, FigY);
			//����� ������������
			for (int i = 0; i < BallAmount; i++) {
				//������������ ����������
				if (Active->Bump(Balls[i]->FitRect())) {
					FigX += Speed;	//�������� ���������� ����������
					//����������� �������� ������
					Active->MoveTo(FigX, FigY);
					return i;		//������� ������ �����������
				}//end if
			}//end for i
			Sleep(50);				//�����
		}//end while

		while (KEY_DOWN(VK_RIGHT)) {	//������� ������  39
			FigX += Speed;			//���������� ����������
			//����������� �������� ������
			Active->MoveTo(FigX, FigY);
			//����� ������������
			for (int i = 0; i < BallAmount; i++) {
				//������������ ����������
				if (Active->Bump(Balls[i]->FitRect())) {
					FigX -= Speed;	//�������� ���������� ����������
					//����������� �������� ������
					Active->MoveTo(FigX, FigY);
					return i;		//������� ������ �����������
				}//end if
			}//end for i
			Sleep(50);				//�����
		}//end while

		while (KEY_DOWN(VK_DOWN)) {	//������� ����  40
			FigY += Speed;			//���������� ����������
			//����������� �������� ������
			Active->MoveTo(FigX, FigY);
			//����� ������������
			for (int i = 0; i < BallAmount; i++) {
				//������������ ����������
				if (Active->Bump(Balls[i]->FitRect())) {
					FigY -= Speed;	//�������� ���������� ����������
					//����������� �������� ������
					Active->MoveTo(FigX, FigY);
					return i;		//������� ������ �����������
				}//end if
			}//end for i
			Sleep(50);				//�����
		}//end while

		while (KEY_DOWN(VK_UP)) {	//������� �����  38
			FigY -= Speed;			//���������� ����������
			//����������� �������� ������
			Active->MoveTo(FigX, FigY);
			//����� ������������
			for (int i = 0; i < BallAmount; i++) {
				//������������ ����������
				if (Active->Bump(Balls[i]->FitRect())) {
					FigY += Speed;	//�������� ���������� ����������
					//����������� �������� ������
					Active->MoveTo(FigX, FigY);
					return i;		//������� ������ �����������
				}//end if
			}//end for i
			Sleep(50);				//�����
		}//end while

		if (KEY_DOWN(VK_ESCAPE)) {	//����� �� ���� �� ������ Esc
			return -1;
		}//end if
	}//end while

}//end Drag()

/*----------------------------------------------------------------------*/
/*   ��������� ����� �� ���������   */
/*----------------------------------*/
int RandomInteger(
	int From,						//������ ������� ���������
	int To,							//������� ������� ���������
	int mode) {						//����� (1 - ������������� ����,
									//0 - ����������(�� ���������)
	//������ ����� � ���������
	int randDigit = rand() % (abs(To - From)) + From;

	//������ �����
	double randSign = (rand() % 20) - 10;
	if ((randSign > 0) || (mode == 1)) {//���� + ��� ����� ��� �����
		return randDigit;
	} else {						//���� -
		return -randDigit;
	}//end if

}//end RandomInteger()

/**********************   End of File CLASSES.�PP   *********************/