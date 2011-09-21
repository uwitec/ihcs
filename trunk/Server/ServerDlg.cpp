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
	//初始化CList控件和header
	m_list.InsertColumn(0,"IP地址");
	m_list.InsertColumn(1,"端口号");

	//设置header的宽度
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

	//创建接收线程
	HANDLE hThread=CreateThread(NULL,0,RecvProc,(LPVOID)pRecvParam,0,NULL);

	//关闭该接收句柄，释放其引用参数
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
	//创建套接字
	m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(INVALID_SOCKET==m_socket)
	{
		MessageBox("套接字创建失败！");
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_family=AF_INET;
//	addrSock.sin_port=htons(atoi(m_txtServerPort));  
	addrSock.sin_port=htons(6000);
	addrSock.sin_addr.S_un.S_addr=htonl(INADDR_ANY);

	int retval;
	//绑定套接字
	retval=bind(m_socket,(SOCKADDR*)&addrSock,sizeof(SOCKADDR));
	if(SOCKET_ERROR==retval)
	{
		closesocket(m_socket);
		MessageBox("绑定失败！");
		return FALSE;
	}
	return TRUE;
}

DWORD WINAPI CServerDlg::RecvProc(LPVOID lpParameter)
{
	//获取主线程传递的套接字和窗口句柄
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
		//接收数据
		retval=recvfrom(sock,recvBuf,200,0,(SOCKADDR*)&addrFrom,&len);
		if(SOCKET_ERROR==retval)
			break;
		sprintf(tempBuf,"%s说：%s",inet_ntoa(addrFrom.sin_addr),recvBuf);
		::PostMessage(hwnd,WM_RECVDATA,0,(LPARAM)tempBuf);
	}
	return 0;

}

void CServerDlg::OnRecvData(WPARAM wParam,LPARAM lParam)
{
	//取出接收到的数据
	CString str=(char *)lParam;
	CString strTemp;

	//获得已有的数据
	GetDlgItemText(IDC_EDIT_RecvMsg,strTemp);
	str+="\r\n";
	str+=strTemp;

	//显示所有接收到的数据
	SetDlgItemText(IDC_EDIT_RecvMsg,str);
}

void CServerDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	//获得对方IP
	DWORD dwIP;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);

	SOCKADDR_IN addrTo;
	addrTo.sin_family=AF_INET;
//	addrTo.sin_port=htons(atoi(m_txtServerPort));
	addrTo.sin_port=htons(6000);
	addrTo.sin_addr.S_un.S_addr=htonl(dwIP);

	CString strSend;

	//获得待发数据
	GetDlgItemText(IDC_EDIT_SendMsg,strSend);

	//发送数据
	sendto(m_socket,strSend,strSend.GetLength()+1,0,(SOCKADDR*)&addrTo,sizeof(SOCKADDR));
	//清空发送编辑框中的内容
	SetDlgItemText(IDC_EDIT_SendMsg," ");
}
