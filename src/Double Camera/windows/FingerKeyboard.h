
// FingerKeyboard.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CFingerKeyboardApp:
// �� Ŭ������ ������ ���ؼ��� FingerKeyboard.cpp�� �����Ͻʽÿ�.
//

class CFingerKeyboardApp : public CWinApp
{
public:
	CFingerKeyboardApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CFingerKeyboardApp theApp;