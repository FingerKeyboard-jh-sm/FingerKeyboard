
// FingerKeyboardDlg.cpp : 구현 파일
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

	m_ctlCob.SetCurSel(0);

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
	if(fk==NULL)
	{
		return;
	}

	if(m_CamDlg.GetSafeHwnd()==NULL)
		m_CamDlg.Create(IDD_CAMERA_SET);
	m_CamDlg.fk=fk;
	m_CamDlg.ShowWindow(SW_SHOW);
}


void CFingerKeyboardDlg::OnBnClickedBtnKeyboard()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString caption;
	((CButton *)GetDlgItem(IDC_BTN_KEYBOARD))->GetWindowTextW(caption);

	fk = new FkFingerKeyboard(0, 0);
	if(!fk->isCameraSet()){
		//Message
		NOTIFYICONDATA nid;    //아이콘을생성하여설정
		ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd1;
		nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_MESSAGE;
		nid.uCallbackMessage = WM_TRAYICON;
		nid.uID = IDH_TRAYICON;
		nid.hIcon = theApp.LoadIcon(IDR_MAINFRAME);
		_tcscpy(nid.szInfoTitle, TEXT("FingerKeyboard"));
		_tcscpy(nid.szInfo, TEXT("카메라를 재설정 하세요. "));
		nid.dwInfoFlags = NIIF_USER; //아이콘도 나오게
		if (!::Shell_NotifyIcon(NIM_MODIFY, &nid))
		{
			::Shell_NotifyIcon(NIM_ADD, &nid);
		}
		delete fk;
		return;
	}

	NOTIFYICONDATA nid;    //아이콘을생성하여설정
	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd1;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_MESSAGE;
	nid.uCallbackMessage = WM_TRAYICON;
	nid.uID = IDH_TRAYICON;
	nid.hIcon = theApp.LoadIcon(IDR_MAINFRAME);
	_tcscpy(nid.szInfoTitle, TEXT("FingerKeyboard"));
	_tcscpy(nid.szInfo, TEXT("마우스로 드래그하여 키보드 영역을 잡으세요.  "));
	nid.dwInfoFlags = NIIF_USER; //아이콘도 나오게
	if (!::Shell_NotifyIcon(NIM_MODIFY, &nid))
	{
		::Shell_NotifyIcon(NIM_ADD, &nid);
	}

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CvRect selectedPaperArea = {NULL, NULL, NULL, NULL};
	//CurrentMode::state = SET_ROI; ??????
	FkCurrentMode::state = SET_KB_REGION;
}


void CFingerKeyboardDlg::OnBnClickedBtnHandchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	FkCurrentMode::state = WAIT_HAND;

}


void CFingerKeyboardDlg::OnBnClickedBtnKeyarea()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//PaperKeyboard_TypeA showKeyButton(PaperKeyboard_TypeA buttonShowImage);
	//IplImage *image = cvLoadImage("button.jpg");
	cvShowImage("Button Area", fk->getButtonImage());

}
