// CMailDemo3.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂߂�O�ɁA'stdafx.h' ���܂߂Ă��������B
#endif

#include "resource.h"		// ���C�� �V���{��


// CCMailDemo3App:
// ���̃N���X�̎����ɂ��ẮACMailDemo3.cpp ���Q�Ƃ��Ă��������B
//

class CCMailDemo3App : public CWinApp
{
public:
	CCMailDemo3App();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CCMailDemo3App theApp;
