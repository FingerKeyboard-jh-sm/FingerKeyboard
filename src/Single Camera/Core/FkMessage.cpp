/**
* @file FkMessage.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 사용자를 위한 안내 메시지
*/
#include"FkMessage.h"
#ifndef _WINDOWS
void FkConsoleMessage::showMessage(char* msg){
	cout<<msg<<endl;
}
#endif

#ifdef _WINDOWS
#include "TrayIconMng.h"
#include "FingerKeyboard.h"
#include "FingerKeyboardDlg.h"
FkWindowsMessage::FkWindowsMessage(){
	message = new WCHAR[100];
}
void FkWindowsMessage::showMessage(char* msg){
	MultiByteToWideChar(CP_ACP, 0,msg, strlen(msg)+1, message, 100);
	NOTIFYICONDATA nid;    //아이콘을생성하여설정
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd2;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_MESSAGE;
	nid.uCallbackMessage = WM_TRAYICON;
	nid.uID = IDH_TRAYICON;
	nid.hIcon = theApp.LoadIcon(IDR_MAINFRAME);
	_tcscpy(nid.szInfoTitle, TEXT("FingerKeyboard"));
	_tcscpy(nid.szInfo, message);
	nid.dwInfoFlags = NIIF_USER; //아이콘도 나오게
	if (!::Shell_NotifyIcon(NIM_MODIFY, &nid))
	{
		::Shell_NotifyIcon(NIM_ADD, &nid);
	}
}
FkWindowsMessage::~FkWindowsMessage(){
	delete message;
}
#endif