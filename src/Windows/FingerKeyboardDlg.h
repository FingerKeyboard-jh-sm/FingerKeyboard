
// FingerKeyboardDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "TrayIconMng.h"
#include "afxcmn.h"

#include "CamSetDialog.h"
#ifndef FK_PROGRAM_
#include "FkFingerKeyboard.h"
#endif
// CFingerKeyboardDlg 대화 상자
class CFingerKeyboardDlg : public CDialogEx
{
// 생성입니다.
public:
	CFingerKeyboardDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	//
	CFingerKeyboardDlg(CWnd* pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT uID);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_FINGERKEYBOARD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctlCob;

	CTrayIconMng m_Tray;

	// 트레이아이콘보이기/숨기기여부
	bool m_bHide;

	// 핑거 키보드 
	FkFingerKeyboard* fk;	
	FkFingerKeyboard* fk;
	// 카메라 설정 대화상자
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
