#pragma once
#include "afx.h"
class CTrayIconMng :
	public CObject
{
public:
	CTrayIconMng(void);
	~CTrayIconMng(void);
	bool m_bAdded;
	// ���̾�αװ������������������� (True : ������)

        bool m_bHide;

        // �˾��޴�����

        void MakePopupMenu(HWND hWnd, int x, int y);

        // �˾��޴����̺�Ʈ�߻���ó���Լ�

        void ProcTrayMsg(HWND hWnd, WPARAM wParam, LPARAM lParam);

        // Ʈ���̾����ܻ���

        BOOL AddTrayIcon(HWND hWnd);

        // Ʈ���̾���������

        BOOL DelTrayIcon(HWND hWnd);

		void MakePopupMenu(void);
};

