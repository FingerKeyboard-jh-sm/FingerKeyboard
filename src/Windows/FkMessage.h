#ifndef FK_MSG_
#define FK_MSG_
class FkMessage{
public:
	virtual void showMessage(char* msg) = 0;
};

#ifdef _WINDOWS
#include "afxwin.h"
#include "stdafx.h"
#define IDH_TRAYICON 0x01
class FkWindowsMessage : public FkMessage{
	HWND hWnd2;
	wchar_t* message;
public:
	void showMessage(char* msg);
	FkWindowsMessage();
	~FkWindowsMessage();
};
#endif
#ifndef _WINDOWS
#include<iostream>
using namespace std;
class FkConsoleMessage : public FkMessage{
public:
	void showMessage(char* msg);
};
#endif
#endif