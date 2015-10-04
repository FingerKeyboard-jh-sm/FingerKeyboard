// CamSetDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "FingerKeyboard.h"
#include "CamSetDialog.h"

// CamSetDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CamSetDialog, CDialogEx)

CamSetDialog::CamSetDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CamSetDialog::IDD, pParent)
{

}

CamSetDialog::~CamSetDialog()
{
}

void CamSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_exposureSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_gainSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_brightSlider);
	DDX_Control(pDX, IDC_SLIDER4, m_contrastSlider);
	DDX_Control(pDX, IDC_SLIDER5, m_chromaSlider);
	DDX_Control(pDX, IDC_SLIDER6, m_whitebalanceSlider);
}


BEGIN_MESSAGE_MAP(CamSetDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_INIT, &CamSetDialog::OnBnClickedBtnInit)
	ON_BN_CLICKED(IDC_BTN_SETUP, &CamSetDialog::OnBnClickedBtnSetup)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CamSetDialog::OnBnClickedBtnCancel)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CamSetDialog 메시지 처리기입니다.


BOOL CamSetDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_exposureSlider.SetRange(-50, 50);
	m_exposureSlider.SetPos(-4);

	m_gainSlider.SetRange(0, 200);
	m_gainSlider.SetPos(100);

	m_brightSlider.SetRange(0, 300);
	m_brightSlider.SetPos(160);

	m_contrastSlider.SetRange(0, 100);
	m_contrastSlider.SetPos(29);

	m_chromaSlider.SetRange(0, 100); // SATURATION
	m_chromaSlider.SetPos(34);

	m_whitebalanceSlider.SetRange(0, 10000);
	m_whitebalanceSlider.SetPos(6820);

	return TRUE; 
}


void CamSetDialog::OnBnClickedBtnInit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_exposureSlider.SetPos(-4);
	m_gainSlider.SetPos(100);
	m_brightSlider.SetPos(160);
	m_contrastSlider.SetPos(29);
	m_chromaSlider.SetPos(34);
	m_whitebalanceSlider.SetPos(6820);

	fk->camera.setBrightness(m_brightSlider.GetPos());
	fk->camera.setContrast(m_contrastSlider.GetPos());
	fk->camera.setSaturation(m_chromaSlider.GetPos());
	fk->camera.setGain(m_gainSlider.GetPos());
	fk->camera.setExposure(m_exposureSlider.GetPos());
	fk->camera.setWhiteBalance(m_whitebalanceSlider.GetPos());
	
}


void CamSetDialog::OnBnClickedBtnSetup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	fk->camera.setBrightness(m_brightSlider.GetPos());
	fk->camera.setContrast(m_contrastSlider.GetPos());
	fk->camera.setSaturation(m_chromaSlider.GetPos());
	fk->camera.setGain(m_gainSlider.GetPos());
	fk->camera.setExposure(m_exposureSlider.GetPos());
	fk->camera.setWhiteBalance(m_whitebalanceSlider.GetPos());
	OnOK();
}


void CamSetDialog::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}


void CamSetDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	fk->camera.setBrightness(m_brightSlider.GetPos());
	fk->camera.setContrast(m_contrastSlider.GetPos());
	fk->camera.setSaturation(m_chromaSlider.GetPos());
	fk->camera.setGain(m_gainSlider.GetPos());
	fk->camera.setExposure(m_exposureSlider.GetPos());
	fk->camera.setWhiteBalance(m_whitebalanceSlider.GetPos());
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
