#pragma once
#include "afx.h"
class CTrayIconMng :
	public CObject
{
public:
	CTrayIconMng(void);
	~CTrayIconMng(void);
	bool m_bAdded;
	// 다이얼로그가감춰진상태인지여부 (True : 숨겨짐)

        bool m_bHide;

        // 팝업메뉴생성

        void MakePopupMenu(HWND hWnd, int x, int y);

        // 팝업메뉴의이벤트발생시처리함수

        void ProcTrayMsg(HWND hWnd, WPARAM wParam, LPARAM lParam);

        // 트레이아이콘생성

        BOOL AddTrayIcon(HWND hWnd);

        // 트레이아이콘제거

        BOOL DelTrayIcon(HWND hWnd);

		void MakePopupMenu(void);
};

