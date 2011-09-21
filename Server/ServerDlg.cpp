// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	m_txtSendMsg = _T("");
	m_txtServerPort = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_EDIT_SendMsg, m_txtSendMsg);
	DDX_Text(pDX, IDC_EDIT_ServerPort, m_txtServerPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECVDATA,OnRecvData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//��ʼ��CList�ؼ���header
	m_list.InsertColumn(0,"IP��ַ");
	m_list.InsertColumn(1,"�˿ں�");

	//����header�Ŀ��
	RECT rectList;
	m_list.GetWindowRect(&rectList);
	int width=rectList.right-rectList.left-2;
	for(int i=0;i<2;i++)
	{
		m_list.SetColumnWidth(i,width/2);
//		m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	}
	InitSocket();

	RECVPARAM *pRecvParam=new RECVPARAM;
	pRecvParam->sock=m_socket;
	pRecvParam->hwnd=m_hWnd;

	//���������߳�
	HANDLE hThread=CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,NULL);

	//�رոý��վ�����ͷ������ò���
	CloseHandle(hThread);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CServerDlg::InitSocket()
{
	//�����׽���
	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_socket)
	{
		MessageBox("�׽��ִ���ʧ�ܣ�");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_family=AF_INET;
//	addrSock.sin_port=htons(atoi(m_txtServerPort));  
	addrSock.sin_port=htons(6000);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);

	int retval;
	//���׽���
	retval=bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		MessageBox("��ʧ�ܣ�");
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI CServerDlg::RecvProc(LPVOID lpParameter)
{
	//��ȡ���̴߳��ݵ��׽��ֺʹ��ھ��
	SOCKET sock=((RECVPARAM*)lpParameter)->sock;
	HWND hwnd=((RECVPARAM*)lpParameter)->hwnd;
	delete lpParameter;

	SOCKADDR_IN addrFrom;
	int len=sizeof(SOCKADDR);

	char recvBuf[200];
	char tempBuf[300];
	int retval;

	while(TRUE)
	{
		//��������
		retval=recvfrom(sock,recvBuf,200,0,(SOCKADDR*)&addrFrom,&len);
		if(SOCKET_ERROR==retval)
			break;
		sprintf(tempBuf,"%s˵��%s",inet_ntoa(addrFrom.sin_addr),recvBuf);
		::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)tempBuf);
	}
	return 0;

}

void CServerDlg::OnRecvData(WPARAM wParam,LPARAM lParam)
{
	//ȡ�����յ�������
	CString str=(char *)lParam;
	CString strTemp;

	//������е�����
	GetDlgItemText(IDC_EDIT_RecvMsg,strTemp);
	str+="\r\n";
	str+=strTemp;

	//��ʾ���н��յ�������
	SetDlgItemText(IDC_EDIT_RecvMsg,str);
}

void CServerDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	//��öԷ�IP
	DWORD dwIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);

	SOCKADDR_IN addrTo;
	addrTo.sin_family=AF_INET;
//	addrTo.sin_port=htons(atoi(m_txtServerPort));
	addrTo.sin_port=htons(6000);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIP);

	CString strSend;

	//��ô�������
	GetDlgItemText(IDC_EDIT_SendMsg,strSend);

	//��������
	sendto(m_socket,strSend,strSend.GetLength()+1,0,(SOCKADDR*)&addrTo,sizeof(SOCKADDR));
	//��շ��ͱ༭���е�����
	SetDlgItemText(IDC_EDIT_SendMsg," ");
}
