#include <windows.h>
//Ѕезродных ».ѕ.
//06/01/16
#include "GetConlWin.h"
/*----------------------------------------------------------------------*/
/*  —оздать консольное окно  */
/*---------------------------*/
HWND GetConcolWindow(){
	char str[128];
	// char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//нова€ верси€ Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определ€ем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}//end GetConcolWindow()

 /******************   End of File GetConWin.cpp  *****************/