// InjectSimpleCodeDlg.h : header file
//

#if !defined(AFX_INJECTSIMPLECODEDLG_H__C4B1CF5C_A147_49B0_AC2B_913091B4B02B__INCLUDED_)
#define AFX_INJECTSIMPLECODEDLG_H__C4B1CF5C_A147_49B0_AC2B_913091B4B02B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInjectSimpleCodeDlg dialog

class CInjectSimpleCodeDlg : public CDialog
{
// Construction
public:
	CInjectSimpleCodeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInjectSimpleCodeDlg)
	enum { IDD = IDD_INJECTSIMPLECODE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInjectSimpleCodeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInjectSimpleCodeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInject();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INJECTSIMPLECODEDLG_H__C4B1CF5C_A147_49B0_AC2B_913091B4B02B__INCLUDED_)
