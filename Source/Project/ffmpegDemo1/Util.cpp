//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   Util.cpp
//* Author   :   liujiquan
//* DateTime :   11/24/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "StdAfx.h"
#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static bool g_ThreadRunning = false;
vector<int64_t>	g_TimestampList;		// ʱ���
int g_VideoFrameCount = 0;				// ʱ�������
int ThreadFunc(void* param)
{
	return 0;
}
bool PlayVedio(char* szFilePath)
{

	return true;
}