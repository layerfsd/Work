#if !defined(AFX_WMPDVD_H__5E7956E4_9A18_4729_9382_6A099AC098F8__INCLUDED_)
#define AFX_WMPDVD_H__5E7956E4_9A18_4729_9382_6A099AC098F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CWMPDVD wrapper class

class CWMPDVD : public COleDispatchDriver
{
public:
	CWMPDVD() {}		// Calls COleDispatchDriver default constructor
	CWMPDVD(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWMPDVD(const CWMPDVD& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIsAvailable(LPCTSTR bstrItem);
	CString GetDomain();
	void topMenu();
	void titleMenu();
	void back();
	void resume();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WMPDVD_H__5E7956E4_9A18_4729_9382_6A099AC098F8__INCLUDED_)
