
// FingerKeyboardDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "FingerKeyboard.h"
#include "FingerKeyboardDlg.h"
HWND hWnd1;
#define IDH_TRAYICON 0x01

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFingerKeyboardDlg 대화 상자



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
	DDX_Control(pDX, IDC_FPS, fpsLabel);
	DDX_Control(pDX, IDC_COM_CAM2, cb_cam2);
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
	ON_STN_CLICKED(IDC_FPS, &CFingerKeyboardDlg::OnStnClickedFps)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO3, &CFingerKeyboardDlg::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COM_CAM2, &CFingerKeyboardDlg::OnCbnSelchangeComCam2)
END_MESSAGE_MAP()


// CFingerKeyboardDlg 메시지 처리기

BOOL CFingerKeyboardDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//m_ctlCob.AddString(_T("cam 0"));
	//m_ctlCob.AddString(_T("cam 1"));
	//m_ctlCob.AddString(_T("cam 2"));
	//m_ctlCob.AddString(_T("cam 3"));

	kbTypeCombo.AddString(_T("Type A"));
	kbTypeCombo.AddString(_T("Type B"));

	cb_cam2.AddString(_T("cam0"));
	cb_cam2.AddString(_T("cam1"));
	cb_cam2.AddString(_T("cam2"));


	cb_cam2.SetCurSel(1);
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

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFingerKeyboardDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFingerKeyboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFingerKeyboardDlg::OnBnClickedBtnCamerasetup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 카메라 설정
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
	SetTimer(1,500,NULL); 
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//cvNamedWindow("Program");
	CString caption;
	((CButton *)GetDlgItem(IDC_BTN_KEYBOARD))->GetWindowTextW(caption);
	FkWindowsMessage msg;
	fk = new FkFingerKeyboard(m_ctlCob.GetCurSel(), cb_cam2.GetCurSel(), kbTypeCombo.GetCurSel());
	if(!fk->isCameraSet()){
		msg.showMessage("카메라를 재설정하세요");
		return;
	}
	/*msg.showMessage("마우스로 드래그하여 키보드 영역을 잡으세요.");*/
	fk->programRun();
}

int CFingerKeyboardDlg::IsOutsideEditorRunning(void)
{
	unsigned long l;

	if(pinfo.hProcess)
	{
		GetExitCodeProcess(pinfo.hProcess, &l);
		if(l==STILL_ACTIVE)
			return -1;       //동작중은 실행하지 않는다. 
	}
	return 0;
}

long CFingerKeyboardDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	m_Tray.ProcTrayMsg(GetSafeHwnd(), wParam, lParam);
	return 0;

}

// 트레이아이콘팝업메뉴의종료메뉴메시지핸들러
void CFingerKeyboardDlg::OnAppExit(void)
{
	m_Tray.DelTrayIcon(GetSafeHwnd());
	CDialog::OnCancel();
}

// 트레이아이콘보이기/숨기기메뉴메시지핸들러
void CFingerKeyboardDlg::OnDialogShow(void)
{
	if(!m_bHide)
		ShowWindow(false);       //보이는상태라면숨기고
	else
		ShowWindow(true);                //숨겨진상태라면보이게
	m_bHide = !m_bHide;
	m_Tray.m_bHide = m_bHide;
}


void CFingerKeyboardDlg::OnBnClickedBtnInit()
{
	cvShowImage("Keyboard Area", fk->preProcessor.paperKeyboardRecognizer.bottomMaskImage);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFingerKeyboardDlg::OnBnClickedBtnHandchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//손 색 재설정
	//FkCurrentMode::state = WAIT_HAND;
	
}


void CFingerKeyboardDlg::OnBnClickedBtnKeyarea()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cvShowImage("Button Area", fk->preProcessor.paperKeyboardRecognizer.buttonImage);
}

void CFingerKeyboardDlg::OnBnClickedBtnExit()
{
	if(fk != NULL){
		//fk->out();
		//fpsLabel.SetWindowText(_T("0 fps"));
		//KillTimer(1);
		delete fk;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFingerKeyboardDlg::OnStnClickedFps()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFingerKeyboardDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//fps 부분
	//SetDlgItemText(IDC_FPS, "니냐니뇨");
	/*CString str;
	str.Format(_T("%.2lf fps"), fk->timeScheduler.fps);
	fpsLabel.SetWindowTextW(str);
	CDialogEx::OnTimer(nIDEvent);*/
}


void CFingerKeyboardDlg::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFingerKeyboardDlg::OnCbnSelchangeComCam2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
