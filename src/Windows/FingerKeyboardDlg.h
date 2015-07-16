
// FingerKeyboardDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "TrayIconMng.h"
#include "afxcmn.h"

#include "CamSetDialog.h"
#ifndef FK_PROGRAM_
#include "FkFingerKeyboard.h"
#endif
// CFingerKeyboardDlg ��ȭ ����
class CFingerKeyboardDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CFingerKeyboardDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	//
	CFingerKeyboardDlg(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_FINGERKEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctlCob;

	CTrayIconMng m_Tray;

	// Ʈ���̾����ܺ��̱�/����⿩��
	bool m_bHide;

	// �ΰ� Ű���� 
	FkFingerKeyboard* fk;	
	FkFingerKeyboard* fk;
	// ī�޶� ���� ��ȭ����
	CamSetDialog m_CamDlg;


    PROCESS_INFORMATION pinfo;

	afx_msg void OnBnClickedBtnKeyboard();
	afx_msg void OnBnClickedBtnCamerasetup();
	afx_msg void OnBnClickedBtnInit();
	int IsOutsideEditorRunning(void);
	
	long OnTrayIcon(WPARAM wParam, LPARAM lParam);
	void OnDialogShow(void);
	void OnAppExit(void);
	afx_msg void OnBnClickedBtnHandchange();
	afx_msg void OnBnClickedBtnKeyarea();
};
