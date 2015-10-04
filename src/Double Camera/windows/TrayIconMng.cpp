#include "stdafx.h"
#include "TrayIconMng.h"
#include "FingerKeyboard.h"
#include "FingerKeyboardDlg.h"

#define IDH_TRAYICON 0x01
#define YM_FROMTRAY WM_USER+1

CTrayIconMng::CTrayIconMng(void)
	: m_bAdded(false)
{
}


CTrayIconMng::~CTrayIconMng(void)
{
}


void CTrayIconMng::MakePopupMenu(HWND hWnd, int x, int y)

{ 

	//팝업메뉴를생성하고메뉴구성

	HMENU hMenu = CreatePopupMenu();

	if(m_bHide)            //다이얼로그가감춰진상태라면

		AppendMenu(hMenu, MF_STRING, WM_DIALOG_SHOW, _T("Show"));

	else                 //다이얼로그가숨겨진상태라면

		AppendMenu(hMenu, MF_STRING, WM_DIALOG_SHOW, _T("Hide"));



	AppendMenu(hMenu, MF_STRING, WM_APP_EXIT, _T("Exit"));



	SetForegroundWindow(hWnd);//생성된팝업메뉴밖을클릭할때팝업닫기

	//팝업메뉴띄우기

	TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, x, y, 0, hWnd, NULL);

}





// 팝업메뉴의이벤트발생시처리함수

void CTrayIconMng::ProcTrayMsg(HWND hWnd, WPARAM wParam, LPARAM lParam)

{

	HMENU hMenu = NULL;

	POINT pos;



	if(lParam == WM_LBUTTONDOWN)

	{

		GetCursorPos(&pos);

		MakePopupMenu(hWnd, pos.x, pos.y); //팝업메뉴생성및출력

	}

}



// 트레이아이콘생성

BOOL CTrayIconMng::AddTrayIcon(HWND hWnd)

{

	if(m_bAdded)           //이미트레이아이콘이있다면종료

		return FALSE;



	NOTIFYICONDATA nid;    //아이콘을생성하여설정

	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

	nid.cbSize = sizeof(NOTIFYICONDATA);

	nid.hWnd = hWnd;

	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	nid.uCallbackMessage = WM_TRAYICON;

	nid.uID = 0;

	nid.hIcon = theApp.LoadIcon(IDR_MAINFRAME);



	if(Shell_NotifyIcon(NIM_ADD, &nid)==0) //트레이아이콘표시

		return FALSE;

	m_bAdded = true;       

	return TRUE;

}



// 트레이아이콘제거

BOOL CTrayIconMng::DelTrayIcon(HWND hWnd)

{

	NOTIFYICONDATA nid;



	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

	nid.cbSize = sizeof(NOTIFYICONDATA);

	nid.hWnd = hWnd;

	nid.uFlags = NULL;

	if(Shell_NotifyIcon(NIM_DELETE, &nid)==0) //트레이아이콘삭제

		return FALSE;

	return TRUE;



}

