
#pragma once
#include "afxcmn.h"
#include "FkFingerKeyboard.h"
// CamSetDialog 대화 상자입니다.

class CamSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CamSetDialog)

public:
	CamSetDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CamSetDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CAMERA_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_exposureSlider;
	CSliderCtrl m_gainSlider;
	CSliderCtrl m_brightSlider;
	CSliderCtrl m_contrastSlider;
	CSliderCtrl m_chromaSlider;
	CSliderCtrl m_whitebalanceSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnBnClickedBtnSetup();
	afx_msg void OnBnClickedBtnCancel();

	// 핑거 키보드 
	FkFingerKeyboard* fk;	

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
