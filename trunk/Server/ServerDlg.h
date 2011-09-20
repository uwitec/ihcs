// ServerDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__96531D59_ED78_42A4_811A_C40982E2B13B__INCLUDED_)
#define AFX_SERVERDLG_H__96531D59_ED78_42A4_811A_C40982E2B13B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_RECVDATA     WM_USER+1

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

class CServerDlg : public CDialog
{
// Construction
public:
//	void OnRecvData(WPARAM wParam,LPARAM lParam);
	static DWORD WINAPI RecvProc(LPVOID lpParameter);
	BOOL InitSocket();
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CListCtrl	m_list;
	CString	m_txtSendMsg;
	CString	m_txtServerPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	afx_msg void OnRecvData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	SOCKET m_socket;
};

struct RECVPARAM
{
	SOCKET sock;    //已创建的套接字
	HWND hwnd;      //对话窗句柄
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__96531D59_ED78_42A4_811A_C40982E2B13B__INCLUDED_)
