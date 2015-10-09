/**
* @file FkMessage.h
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 추상 클래스인 FkMessage Class 정의
*/
#ifdef _WINDOWS
#include "afxwin.h"
#include "stdafx.h"
#endif
#ifdef WIN32
#include<Windows.h>
#endif

#ifndef FK_MSG_
#define FK_MSG_
class FkMessage{
public:
	virtual void showMessage(char* msg) = 0;
};

#ifdef _WINDOWS
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