
// FingerKeyboardDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "FingerKeyboard.h"
#include "FingerKeyboardDlg.h"
#include "afxdialogex.h"

HWND hWnd1;
#define IDH_TRAYICON 0x01

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFingerKeyboardDlg ��ȭ ����



CFingerKeyboardDlg::CFingerKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFingerKeyboardDlg::IDD, pParent)
	, m_bHide(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CFingerKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ctlCob);
	DDX_Control(pDX, IDC_BTN_EXIT, btnExit);
	DDX_Control(pDX, IDC_COMBO2, kbTypeCombo);
}

BEGIN_MESSAGE_MAP(CFingerKeyboardDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_KEYBOARD, &CFingerKeyboardDlg::OnBnClickedBtnKeyboard)
	ON_BN_CLICKED(IDC_BTN_CAMEASETUP, &CFingerKeyboardDlg::OnBnClickedBtnCamerasetup)
	ON_BN_CLICKED(IDC_BTN_INIT, &CFingerKeyboardDlg::OnBnClickedBtnInit)
	ON_MESSAGE(WM_TRAYICON, OnTrayIcon)
	ON_COMMAND(WM_APP_EXIT, OnAppExit)
	ON_COMMAND(WM_DIALOG_SHOW, OnDialogShow)

	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BTN_HANDCHANGE, &CFingerKeyboardDlg::OnBnClickedBtnHandchange)
	ON_BN_CLICKED(IDC_BTN_KEYAREA, &CFingerKeyboardDlg::OnBnClickedBtnKeyarea)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CFingerKeyboardDlg::OnBnClickedBtnExit)
END_MESSAGE_MAP()


// CFingerKeyboardDlg �޽��� ó����

BOOL CFingerKeyboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//m_ctlCob.AddString(_T("cam 0"));
	//m_ctlCob.AddString(_T("cam 1"));
	//m_ctlCob.AddString(_T("cam 2"));
	//m_ctlCob.AddString(_T("cam 3"));

	kbTypeCombo.AddString(_T("Type A"));
	kbTypeCombo.AddString(_T("Type B"));

	m_ctlCob.SetCurSel(0);
	kbTypeCombo.SetCurSel(0);
	m_Tray.m_bHide = m_bHide;
	m_Tray.AddTrayIcon(GetSafeHwnd());

	pinfo.hProcess=NULL;
	pinfo.hThread=NULL;
	pinfo.dwProcessId=0L;
	pinfo.dwThreadId=0L;

	fk=NULL;

	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(1000, 200, rect.Width(), rect.Height());

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CFingerKeyboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFingerKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFingerKeyboardDlg::OnBnClickedBtnCamerasetup()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ī�޶� ����
	if(fk==NULL){
		return;
	}
	if(m_CamDlg.GetSafeHwnd()==NULL)
		m_CamDlg.Create(IDD_CAMERA_SET);
	m_CamDlg.fk=fk;
	m_CamDlg.ShowWindow(SW_SHOW);
}


void CFingerKeyboardDlg::OnBnClickedBtnKeyboard()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString caption;
	((CButton *)GetDlgItem(IDC_BTN_KEYBOARD))->GetWindowTextW(caption);
	FkWindowsMessage msg;
	fk = new FkFingerKeyboard(m_ctlCob.GetCurSel(), kbTypeCombo.GetCurSel());
	if(!fk->isCameraSet()){
		msg.showMessage("ī�޶� �缳���ϼ���");
		return;
	}
	msg.showMessage("���콺�� �巡���Ͽ� Ű���� ������ ��������.");
	fk->start();
}

int CFingerKeyboardDlg::IsOutsideEditorRunning(void)
{
	unsigned long l;

	if(pinfo.hProcess)
	{
		GetExitCodeProcess(pinfo.hProcess, &l);
		if(l==STILL_ACTIVE)
			return -1;       //�������� �������� �ʴ´�. 
	}
	return 0;
}

long CFingerKeyboardDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	m_Tray.ProcTrayMsg(GetSafeHwnd(), wParam, lParam);
	return 0;

}

// Ʈ���̾������˾��޴�������޴��޽����ڵ鷯
void CFingerKeyboardDlg::OnAppExit(void)
{
	m_Tray.DelTrayIcon(GetSafeHwnd());
	CDialog::OnCancel();
}

// Ʈ���̾����ܺ��̱�/�����޴��޽����ڵ鷯
void CFingerKeyboardDlg::OnDialogShow(void)
{
	if(!m_bHide)
		ShowWindow(false);       //���̴»��¶������
	else
		ShowWindow(true);                //���������¶�麸�̰�
	m_bHide = !m_bHide;
	m_Tray.m_bHide = m_bHide;
}


void CFingerKeyboardDlg::OnBnClickedBtnInit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	FkCurrentMode::state = SET_KB_REGION;
}


void CFingerKeyboardDlg::OnBnClickedBtnHandchange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	FkCurrentMode::state = WAIT_HAND;

}


void CFingerKeyboardDlg::OnBnClickedBtnKeyarea()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	cvShowImage("Button Area", fk->getButtonImage());
	}

void CFingerKeyboardDlg::OnBnClickedBtnExit()
{
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
