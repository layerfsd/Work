//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, Liujiquan Company�B( All rights reserved. )
//* FileName�F      MemoryUtil.h
//* Version �F      1.0
//* Author  �F      Liujiquan
//* Date    �F      2014�N7��11��
//* Comment �F      ��������I�ꍱ����
//*-----------------------------------------------------------------------------*/
#ifndef __MEMORYUTIL_H_F1030131_E1DE_41f1_B217_C701552E9345__
#define __MEMORYUTIL_H_F1030131_E1DE_41f1_B217_C701552E9345__
#pragma once

#include <afxtempl.h>
#include <WTypes.h>
#include <TlHelp32.h>

//////////////////////////////////////////////////////////////////////////
// �G                                                                  
#define PAGE_SIZE       0x00001000              // �v�Z�@�ҔF�ő召 4MB     4 * 1024
#define ADDRESS_BEGIN   0x000A0000              // �����͚�BEGIN
#define ADDRESS_END     0x80000000              // �����͚�END
//////////////////////////////////////////////////////////////////////////
// ���\�
static CArray<DWORD, DWORD> g_dwAddressArrTemp;        // �Վ�����
static int          g_findFlag;
static HANDLE       g_findhProcess;
static TCHAR        g_findText[MAX_PATH];
typedef struct tag_SEARCHDATA                           // �Վ��ҝɌ��\� [�����B�ҝɏo������]
{
    int     flag;
    TCHAR   findText[MAX_PATH];
    HANDLE  hProcess;
public:
    tag_SEARCHDATA(HANDLE process, int nFlag, LPCTSTR pszFinText)
    {
        hProcess = process;
        flag = nFlag;
        memset(findText, 0x00, MAX_PATH);
        memcpy(findText, pszFinText, strlen(pszFinText) > MAX_PATH ? MAX_PATH : strlen(pszFinText));
    }
    tag_SEARCHDATA& operator=(tag_SEARCHDATA& entry)
    {
        this->hProcess = entry.hProcess;
        this->flag = entry.flag;
        memset(this->findText, 0x00, MAX_PATH);
        memcpy(this->findText, entry.findText, MAX_PATH);

        return *this;
    }
}SEARCHDATA, *PSEARCHDATA;
////////////////////////////////////////////////////////////////////////////
// ���p����
static BOOL g_IsSearching = FALSE;                     // �c�O���ݝr������
BOOL GfxGetSearchStatus();                                                                                  // �l���c�O�r��status
void FlushAddress(CArray<DWORD, DWORD>& dwAddrArr);                                                         // ���VAddress
BOOL OnBeginSearch(HANDLE hProcess, int flag, LPCTSTR findtext, CArray<DWORD, DWORD>& dwAddrArr);           // �J�n�r��
BOOL OnResetSearch(HANDLE& hProcess);                                                                       // �d�u
BOOL OnModifyMemory(HANDLE hProcess, DWORD dwAddress, int flag, LPCTSTR modifyText);                        // �C������    
//////////////////////////////////////////////////////////////////////////
// �r������
static HANDLE g_Thead = NULL;                          // �����啿 
static DWORD WINAPI ThreadFunc_(LPVOID param);                                                              // ��������                   
DWORD WINAPI ThreadFunc(HANDLE hProcess, int flag, LPCTSTR findtext);                                       // �������ɛ���
//////////////////////////////////////////////////////////////////////////////
// �㏕����
BOOL ImproveTokenPrivilege();                                                                               // �񏡖{�����I�܌�
static BOOL g_bFirstSerach = TRUE;              // �񎟝r��flag 
void SearchMemoryAddress(HANDLE hProcess, int flag, LPCTSTR findtext, CArray<DWORD, DWORD>& dwAddrArr);     // �r���i���ɝ��n���W��
BOOL BoolMemoryDataIsOK(HANDLE hProcess, DWORD dwAddrBase, int flag, LPCTSTR findtext);                     // �w���������OK
BOOL WriteBuffer(HANDLE hProcess, DWORD dwAddr, LPCTSTR buffer, UINT nSize);                                // �������ɝ�
BOOL Compare(LPCTSTR szSrc, LPCTSTR szSrc2, UINT nLen);                                                     // ��������r
void ReadMemory(HANDLE hProcess, DWORD dwAddrBase, int flag, LPCTSTR findtext, CArray<int, int>& indexArr); // �r���w��ɝ��I�n���W��
//////////////////////////////////////////////////////////////////////////
// �ɝ���r����
void FindByte(LPCTSTR szSrc, BYTE byteData, UINT nSize, CArray<int, int>& indexArr);                        // �r��BYTE
void FindSHORT(LPCTSTR szSrc, SHORT shortData, UINT nSize, CArray<int, int>& indexArr);                     // �r��SHORT
void FindINT(LPCTSTR szSrc, INT intData, UINT nSize, CArray<int, int>& indexArr);                           // �r��INT
void FindFLOAT(LPCTSTR szSrc, float floatData, UINT nSize, CArray<int, int>& indexArr);                     // �r��FLOAT
void FindDOUBLE(LPCTSTR szSrc, DOUBLE doubleData, UINT nSize, CArray<int, int>& indexArr);                  // �r��DOUBLE
void FindStr(LPCTSTR szSrc, LPCTSTR szFind, UINT nSize, CArray<int, int>& indexArr);                        // �r��������
//////////////////////////////////////////////////////////////////////////
// �i��exe�r������
typedef struct tagPROCESSENTRY32_
{
    DWORD   dwSize;
    DWORD   cntUsage;
    DWORD   th32ProcessID;          // this process
    ULONG_PTR th32DefaultHeapID;
    DWORD   th32ModuleID;           // associated exe
    DWORD   cntThreads;
    DWORD   th32ParentProcessID;    // this process's parent process
    LONG    pcPriClassBase;         // Base priority of process's threads
    DWORD   dwFlags;
    CHAR    szExeFile[MAX_PATH];    // Path
// 2014.07.11 Ver1.00 �yPROCESSENTRY32���l�^�Z���d�ځzStart
public:
    tagPROCESSENTRY32_& operator=(tagPROCESSENTRY32_& entry)
    {
        this->dwSize = entry.dwSize;
        this->cntUsage = entry.cntUsage;
        this->th32ProcessID = entry.th32ProcessID;
        this->th32DefaultHeapID = entry.th32DefaultHeapID;
        this->th32ModuleID = entry.th32ModuleID;
        this->cntThreads = entry.cntThreads;
        this->th32ParentProcessID = entry.th32ParentProcessID;
        this->pcPriClassBase = entry.pcPriClassBase;
        this->dwFlags = entry.dwFlags;
        this->pcPriClassBase = entry.pcPriClassBase;
        memcpy(this->szExeFile, entry.szExeFile, MAX_PATH);

        return *this;
    }
// 2014.07.11 Ver1.00 �yPROCESSENTRY32���l�^�Z���d�ځzEnd
} PROCESSENTRY32_;
void FlushProcessInfo(CArray<PROCESSENTRY32_, PROCESSENTRY32_>& processList);                                 // �i��exe�r������
///////////////////////////////////////////////////////////////////
// Message
#define SEARCH_MSG  WM_USER+1
static HWND m_ParentHwnd;
void SetParentHwnd(HWND hwnd);
#endif//__MEMORYUTIL_H_F1030131_E1DE_41f1_B217_C701552E9345__