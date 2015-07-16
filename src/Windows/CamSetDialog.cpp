// CamSetDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "FingerKeyboard.h"
#include "CamSetDialog.h"
#include "afxdialogex.h"


// CamSetDialog ��ȭ �����Դϴ�.

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


// CamSetDialog �޽��� ó�����Դϴ�.


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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_exposureSlider.SetPos(-4);
	m_gainSlider.SetPos(100);
	m_brightSlider.SetPos(160);
	m_contrastSlider.SetPos(29);
	m_chromaSlider.SetPos(34);
	m_whitebalanceSlider.SetPos(6820);

	fk->getCamera().setBrightness(m_brightSlider.GetPos());
	fk->getCamera().setContrast(m_contrastSlider.GetPos());
	fk->getCamera().setSaturation(m_chromaSlider.GetPos());
	fk->getCamera().setGain(m_gainSlider.GetPos());
	fk->getCamera().setExposure(m_exposureSlider.GetPos());
	fk->getCamera().setWhiteBalance(m_whitebalanceSlider.GetPos());
	
}


void CamSetDialog::OnBnClickedBtnSetup()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	fk->getCamera().setBrightness(m_brightSlider.GetPos());
	fk->getCamera().setContrast(m_contrastSlider.GetPos());
	fk->getCamera().setSaturation(m_chromaSlider.GetPos());
	fk->getCamera().setGain(m_gainSlider.GetPos());
	fk->getCamera().setExposure(m_exposureSlider.GetPos());
	fk->getCamera().setWhiteBalance(m_whitebalanceSlider.GetPos());
	OnOK();
}


void CamSetDialog::OnBnClickedBtnCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}


void CamSetDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	fk->getCamera().setBrightness(m_brightSlider.GetPos());
	fk->getCamera().setContrast(m_contrastSlider.GetPos());
	fk->getCamera().setSaturation(m_chromaSlider.GetPos());
	fk->getCamera().setGain(m_gainSlider.GetPos());
	fk->getCamera().setExposure(m_exposureSlider.GetPos());
	fk->getCamera().setWhiteBalance(m_whitebalanceSlider.GetPos());
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
