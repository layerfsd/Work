// ModifyMemory.h : 
//
#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂߂�O�ɁA'stdafx.h' ���܂߂Ă��������B
#endif
#include "resource.h"	
class CModifyMemoryApp : public CWinApp
{
public:
	CModifyMemoryApp();
	public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
extern CModifyMemoryApp theApp;
