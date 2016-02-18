// ModifyMemoryDlg.h :
//
#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <afxtempl.h>

class CModifyMemoryDlg : public CDialog
{
public:
    CModifyMemoryDlg(CWnd* pParent = NULL);	
    ~CModifyMemoryDlg()
    {
        if(m_Process)
        {
            CloseHandle(m_Process);
            m_Process = NULL;
        }
    }
	enum { IDD = IDD_MODIFYMEMORY_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	
protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    void InitInfo();                        // ���n���M��
    void GetProcessInfo();                  // �l������M��
public:
    CListCtrl m_ProcessList;
    CListBox m_MemAddrList;
    CComboBox m_CmbDataType;

    CArray<DWORD, DWORD>    m_AddressArr;   // �����n���W��
    BOOL                    m_bRun;         // ��ꎟ�r��Flag
    HANDLE                  m_Process;      // �i���啿
public:
    afx_msg void OnBnClickedBtnRestart();
    afx_msg void OnBnClickedBtnRefresh();
    afx_msg void OnBnClickedBtnRun();
    afx_msg void OnBnClickedBtnModify();
    LRESULT OnSearchFinish(WPARAM wparam, LPARAM lparam);
};