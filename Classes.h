#pragma once
/*----------------------------------------------------------------------*/
/*                          � � � �    � � � � � �                      */
/*----------------------------------------------------------------------*/

/*------------------------------ ����� ���� ----------------------------*/
class Color {
private:
	int Red;						//�������
	int Green;						//�������
	int Blue;						//�����

public:
	Color							//�����������
		(int InitRed = 0, int InitGreen = 0, int InitBlue = 0);
	~Color(void) {};				//����������
	int GetRed(void);				//�������� �������
	int GetGreen(void);				//�������� �������
	int GetBlue(void);				//�������� �����
	void SetColor					//��������� ����
		(int NewRed = 0, int NewGreen = 0, int NewBlue = 0);

};//end class Color

/*------------------------- ����� �������������� -----------------------*/
class Location {
protected:
	int X;							//���������� X
	int Y;							//���������� Y

public:
	Location(int InitX, int InitY); //�����������
	~Location(void) {};				//����������
	int GetX(void);					//�������� ���������� X
	int GetY(void);					//�������� ���������� Y

};//end class Location

/*----------------------------- �����  ����� ---------------------------*/
class Point : public Location {
protected:
	bool Visible;					//���������
	Color Clr;						//����

public:
	Point							//�����������
		(int InitX, int InitY, Color InitClr = { 0, 0, 0 });
	~Point(void) {};				//����������
	bool IsVisible(void);			//�������� ����������
	void MoveTo(int NewX, int NewY);//����������� ������
	
	//����������� ������
	virtual void Show(void);		//�������� ������
	virtual void Hide(void);		//������ ������
	virtual void Resize(double Scale) = 0;//�������� ������ ������

};//end class Point

/*-------------------------- ����� ������������� -----------------------*/
class Rect : public Point {
private:
	int A;							//�������������� �������
	int B;							//������������ �������
public:
	Rect							//�����������
		(int InitX = 10, int InitY = 10, 
		 int InitA = 10, int InitB = 10, 
		 Color InitClr = { 0, 0, 0 });
	~Rect(void) {};					//����������
	int GetA(void);					//�������� �������������� �������
	int GetB(void);					//�������� ������������ �������
	Rect FitRect(void);				//������� ������������� � �������������

	//������������� ������ �� Point
	void Show(void);				//�������� �������������
	void Hide(void);				//������ �������������
	void Resize(double Scale);		//�������� ������ ��������������

};//end class Rect

/*------------------------------ ����� ���� ----------------------------*/
class Circle : public Point {
protected:		
	int Radius;						//������
public:
	Circle							//�����������
	(int InitX = 10, int InitY = 10, 
	 int InitRdius = 10, 
	 Color InitClr = { 0, 0, 0 });
	~Circle(void) {};				//����������
	int GetRadius(void);			//�������� ������
	Rect FitRect(void);				//������� ���� � �������������

	//������������� ������ �� Point
	void Show(void);				//�������� ����
	void Hide(void);				//������ ����
	void Resize(double Scale);		//�������� ������ �����

};//end class Circle

/*--------------------------- ����� ����������� ------------------------*/
class Triangle : public Point {
private:
	int O;							//���������
	int H;							//������
public:
	Triangle						//�����������
		(int InitX = 10, int InitY = 10, 
		 int InitO = 10, int InitH = 10,
		 Color InitClr = { 0, 0, 0 });
	~Triangle(void) {};				//����������
	Rect FitRect(void);				//������� ���������� � �������������

	//������������� ������ �� Point
	void Show(void);				//�������� �����������
	void Hide(void);				//������ �����������
	void Resize(double Scale);		//�������� ������ ������������

};//end class Triangle

/*---------------------------- ��������� ��� ---------------------------*/
class IHouse {
public:
	IHouse(void) {};				//�����������
	virtual ~IHouse(void) {};		//����������
	virtual int GetWidth(void) = 0;	//�������� ������
	virtual int GetHeight(void) = 0;//�������� ������
	virtual bool Bump(Rect Obj) = 0;//��������� ������������ � ��������

	/*---------------------��������� ��������� ����---------------------*/
	virtual void Roof(bool mode) = 0;//�����
	virtual void Wall(bool mode) = 0;//����� � ���������
	virtual void Chimney(bool mode) = 0;//�����
	virtual void Window(void) = 0;	//����
	virtual void Door(void) = 0;	//�����
	/*------------------------------------------------------------------*/

};//end class IHouse

/*------------------------------ �����  ��� ----------------------------*/
class House : public Point, public IHouse {
protected:
	int Width;						//������
	int Height;						//������
public:
	House(void);					//�����������
	~House(void) {};				//����������
	int GetWidth(void);				//�������� ������
	int GetHeight(void);			//�������� ������
	bool Bump(Rect Obj);			//��������� ������������ � ��������

	/*---------------------��������� ��������� ����---------------------*/
	virtual void Roof(bool mode);	//�����
	virtual void Wall(bool mode);	//����� � ���������
	virtual void Chimney(bool mode);//�����
	virtual void Window(void);		//����
	virtual void Door(void);		//�����
	/*------------------------------------------------------------------*/

	//������������� ������ �� Point
	void Show(void);				//�������� ���
	void Hide(void);				//������ ���
	void Resize(double Scale);		//�������� ������ ����

};//end class House

/*-------------------------- ����� ������� ��� -------------------------*/
class RumpledHouse : public House {
public:
	RumpledHouse(void) : House() {};//�����������
	~RumpledHouse(void) {};			//����������

	/*---------------------��������� ��������� ����---------------------*/
	virtual void Wall(bool mode);	//����� � ���������
	virtual void Chimney(bool mode) {};//�����
	virtual void Window(void);		//����
	virtual void Door(void);		//�����
	/*------------------------------------------------------------------*/

};//end class RumpledHouse

/*-------------------------- ����� ������ ��� --------------------------*/
class PoorHouse : public House {
public:
	PoorHouse(void) : House() {};	//�����������
	~PoorHouse(void) {};			//����������

	/*---------------------��������� ��������� ����---------------------*/
	virtual void Wall(bool mode);	//����� � ���������
	virtual void Chimney(bool mode);//�����
	virtual void Window(void);		//����
	virtual void Door(void);		//�����
	/*------------------------------------------------------------------*/

};//end class PoorHouse

/*------------------------- ����� ������� ��� --------------------------*/
class RichHouse : public House {
public:
	RichHouse(void) : House() {};	//�����������
	~RichHouse(void) {};			//����������

};//end class RichHouse

/*------------------------ ����� ��������� ��� -------------------------*/
class MagicHouse : public RichHouse {
public:
	MagicHouse(void) : RichHouse() {};//�����������
	~MagicHouse(void) {};			//����������

	/*---------------------��������� ��������� ����---------------------*/
	virtual void Roof(bool mode) {};//�����
	virtual void Chimney(bool mode) {};//�����
	/*------------------------------------------------------------------*/

};//end class MagicHouse

/*------------------------------ ����� ��� -----------------------------*/
class Ball : public Circle {
protected:
	int Energy;						//���������� �������
public:
	Ball							//�����������
	(int InitX = 10, int InitY = 10, 
		Color InitClr = { 0, 0, 0 }, int InitEnergy = 0);
	~Ball(void) {};					//����������
	int GetEnergy(void);			//�������� ���������� �������

};//end class Ball

/*-------------------------- ����� ������ ��� --------------------------*/
class BadBall : public Ball {
public:
	BadBall							//�����������
	(int InitX = 10, int InitY = 10) 
		: Ball(InitX, InitY, { 255, 0, 0 }, -1) {};
	~BadBall(void) {};				//����������

};//end class BadBall

/*-------------------------- ����� ������� ��� -------------------------*/
class GoodBall : public Ball {
public:
	GoodBall						//�����������
	(int InitX = 10, int InitY = 10)
		: Ball(InitX, InitY, { 0, 255, 0 }, 1) {};
	~GoodBall(void) {};				//����������

};//end class GoodBall

/*------------------------ ����� ���������� ��� ------------------------*/
class MagicBall : public Ball {
public:
	MagicBall						//�����������
	(int InitX = 10, int InitY = 10)
		: Ball(InitX, InitY, { 255, 0, 255 }, 2) {};
	~MagicBall(void) {};			//����������

};//end class MagicBall

/*----------------------------------------------------------------------*/
/*                  � � � � � � � � �    � � � � � � �                  */
/*----------------------------------------------------------------------*/

bool BetweenCoords	(int Check, int A, int B);
int Drag			(House* Active, Ball** Balls, int BallAmount, int Speed);
int RandomInteger	(int From, int To, int mode = 0);

/***********************   End of File CLASSES.H   **********************/