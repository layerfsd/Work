// ffmpegDemo1Dlg.h : header file
//

#if !defined(AFX_FFMPEGDEMO1DLG_H__FC0A1F2C_8157_41D8_A109_36ADB0309577__INCLUDED_)
#define AFX_FFMPEGDEMO1DLG_H__FC0A1F2C_8157_41D8_A109_36ADB0309577__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFfmpegDemo1Dlg dialog

class CFfmpegDemo1Dlg : public CDialog
{
// Construction
public:
	CFfmpegDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFfmpegDemo1Dlg)
	enum { IDD = IDD_FFMPEGDEMO1_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFfmpegDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFfmpegDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFMPEGDEMO1DLG_H__FC0A1F2C_8157_41D8_A109_36ADB0309577__INCLUDED_)
