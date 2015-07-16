#pragma once
#include "afxcmn.h"
#ifndef FK_PROGRAM_
#include "FkFingerKeyboard.h"
#endif
// CamSetDialog ��ȭ �����Դϴ�.

class CamSetDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CamSetDialog)

public:
	CamSetDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CamSetDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CAMERA_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

	// �ΰ� Ű���� 
	FkFingerKeyboard* fk;	

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
