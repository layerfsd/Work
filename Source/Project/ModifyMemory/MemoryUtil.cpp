#include "MemoryUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// -----------------------------------------------------------//
// Function:    OnBeginSearch
// Param        HANDLE                  hProcess
//              int                     flag
//              LPCTSTR                 findtext
//              LPCTSTR                 findtext
//              CArray<DWORD, DWORD>&   dwAddrArr
// Return  :    BOOL 
// meaning :    
// -----------------------------------------------------------//
BOOL OnBeginSearch(HANDLE hProcess, int flag, LPCTSTR findtext, CArray<DWORD, DWORD>& dwAddrArr)
{
    // �������� ���� �r��������
    if(g_Thead || g_IsSearching)
    {
        return FALSE;
    }
    // �N������
    SEARCHDATA data(hProcess, flag, findtext);
    g_dwAddressArrTemp.RemoveAll();
    g_dwAddressArrTemp.Append(dwAddrArr);
    //
    g_findFlag = data.flag;
    g_findhProcess = data.hProcess;
    memcpy(g_findText, data.findText, MAX_PATH);
    g_Thead = CreateThread(NULL, 0, ThreadFunc_, (LPVOID)&data, 0, 0);   
    
    return g_Thead == NULL;
}

// -----------------------------------------------------------//
// Function:    ThreadFunc_
// Param        LPVOID        param
// Return  :    DWORD WINAPI 
// meaning :    ��������
// -----------------------------------------------------------//
DWORD WINAPI ThreadFunc_(LPVOID param)
{
    SEARCHDATA* pData = (SEARCHDATA*)param;
    if(pData)
    {
//        ThreadFunc(pData->hProcess, pData->flag, pData->findText);
        ThreadFunc(g_findhProcess, g_findFlag, g_findText);
    }

    return 0;
}

// -----------------------------------------------------------//
// Function:    GfxGetSearchStatus
// Param                
// Return  :    BOOL 
// meaning :    �l���c�O�r��status
// -----------------------------------------------------------//
BOOL GfxGetSearchStatus()   
{   
    return g_IsSearching;  
}  

// -----------------------------------------------------------//
// Function:    FlushAddress
// Param        CArray<DWORD, DWORD>&        dwAddrArr               
// Return  :    void 
// meaning :    ���VAddress
// -----------------------------------------------------------//
void FlushAddress(CArray<DWORD, DWORD>& dwAddrArr)
{    
    dwAddrArr.RemoveAll(); 
    dwAddrArr.Append(g_dwAddressArrTemp); 
} 

// -----------------------------------------------------------//
// Function:    ThreadFunc
// Param        HANDLE        hProcess
//              int        flag
//              LPCTSTR        findtext
// Return  :    DWORD WINAPI 
// meaning :    �������ɛ���
// -----------------------------------------------------------//
DWORD WINAPI ThreadFunc(HANDLE hProcess, int flag, LPCTSTR findtext)
{
    SearchMemoryAddress(hProcess, flag, findtext, g_dwAddressArrTemp);
    
    return 0;
}

// -----------------------------------------------------------//
// Function:    OnResetSearch
// Param        HANDLE        hProcess
// Return  :    BOOL 
// meaning :    �d�u  
// -----------------------------------------------------------//
BOOL OnResetSearch(HANDLE& hProcess)
{
    // 萕i��
    if(hProcess)
    {
        CloseHandle(hProcess);
        hProcess = NULL;
    }
    g_bFirstSerach = TRUE;

    return TRUE;
}

// -----------------------------------------------------------//
// Function:    OnModifyMemory
// Param        HANDLE        hProcess
//              DWORD        dwAddress
//              int        flag
//              LPCTSTR        modifyText
// Return  :    BOOL 
// meaning :    �C�������ɝ�
// -----------------------------------------------------------//
BOOL OnModifyMemory(HANDLE hProcess, DWORD dwAddress, int flag, LPCTSTR modifyText)
{
    BOOL bRet = FALSE;
    if(strlen(modifyText) == 0)
    {
        return FALSE;
    }

    switch(flag)
    {
    case 0:
        {
            BYTE value = (BYTE)atoi(modifyText);
            bRet = WriteBuffer(hProcess, dwAddress, (LPCTSTR)&value, sizeof(BYTE));
        }
        break;
    case 1:
        {
            SHORT value = (SHORT)atoi(modifyText);
            bRet = WriteBuffer(hProcess, dwAddress, (LPCTSTR)&value, sizeof(SHORT));
        }
        break;
    case 2:
        {
            INT value = (INT)atoi(modifyText);
            bRet = WriteBuffer(hProcess, dwAddress, (LPCTSTR)&value, sizeof(INT));
        }
        break;
    case 3:
        {
            FLOAT value = (FLOAT)atof(modifyText);
            bRet = WriteBuffer(hProcess, dwAddress, (LPCTSTR)&value, sizeof(FLOAT));
        }
        break;
    case 4:
        {
            DOUBLE value = (DOUBLE)atof(modifyText);
            bRet = WriteBuffer(hProcess, dwAddress, (LPCTSTR)&value, sizeof(DOUBLE));
        }
        break;
    case 5:
        bRet = WriteBuffer(hProcess, dwAddress, modifyText, strlen(modifyText));
        break;
    }

    return bRet;
}

// -----------------------------------------------------------//
// Function:    ImproveTokenPrivilege
// Param                
// Return  :    BOOL  
// meaning :    �񏡗ߔv�܌� [�ۑ��\���l�擞�ꕔ������]
// -----------------------------------------------------------//
BOOL  ImproveTokenPrivilege() 
{
    HANDLE hToken = NULL;
    LUID luid;
    TOKEN_PRIVILEGES tp;

    if(OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        // �ߔvvalue
        if(LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
        {
            tp.PrivilegeCount = 1;
            tp.Privileges->Luid = luid;
            tp.Privileges->Attributes = SE_PRIVILEGE_ENABLED;

            // ����
            if(AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
            {
                DWORD dwError = GetLastError();
                if(dwError == 0)
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

// -----------------------------------------------------------//
// Function:    BoolMemoryDataIsOK
// Param        HANDLE          hProcess    �i��
//              DWORD           dwAddrBase  �n��
//              int             flag        �ɝ��ތ^
//              LPCTSTR         findtext    �ɝ�
// Return  :    BOOL 
// meaning :    �w���������OK
// -----------------------------------------------------------//
BOOL BoolMemoryDataIsOK(HANDLE hProcess, DWORD dwAddrBase, int flag, LPCTSTR findtext)
{   
    SIZE_T nReadSize;       
    BOOL bRet = FALSE;      
    DWORD dwprotect;        // Page�ی�

    switch(flag)
    {
    case 0://BYTE
        {
            BYTE findValue, memValue ;
            findValue = (BYTE)atoi(findtext);
            if(findValue == 0)      {   return FALSE;   }
            bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(BYTE), PAGE_READWRITE, &dwprotect);
            if(bRet == FALSE)   {   return FALSE;   }
            bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, (LPVOID)&memValue, sizeof(BYTE), &nReadSize);
            if(bRet == FALSE)
            {
                ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(BYTE), dwprotect, 0);
                return  FALSE;
            }
            ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(BYTE), dwprotect, 0);

            return memValue == findValue;
        }
        break;
    case 1://SHORT
        {
            SHORT findValue, memValue ;
            findValue = (SHORT)atoi(findtext);
            if(findValue == 0)      {   return FALSE;   }
            bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(SHORT), PAGE_READWRITE, &dwprotect);
            if(bRet == FALSE)   {   return FALSE;   }
            bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, (LPVOID)&memValue, sizeof(SHORT), &nReadSize);
            if(bRet == FALSE)
            {
                ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(SHORT), dwprotect, 0);
                return  FALSE;
            }
            ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(SHORT), dwprotect, 0);

            return memValue == findValue;
        }
        break;
    case 2://INT
        {
            INT findValue, memValue ;
            findValue = (INT)atoi(findtext);
            if(findValue == 0)      {   return FALSE;   }
            bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(INT), PAGE_READWRITE, &dwprotect);
            if(bRet == FALSE)   {   return FALSE;   }
            bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, (LPVOID)&memValue, sizeof(INT), &nReadSize);
            if(bRet == FALSE)
            {
                ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(INT), dwprotect, 0);
                return  FALSE;
            }
            ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(INT), dwprotect, 0);

            return memValue == findValue;
        }
        break;
    case 3://FLOAT
        {
            FLOAT findValue, memValue ;
            findValue = (FLOAT)atof(findtext);
            if(findValue == 0)      {   return FALSE;   }
            bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(FLOAT), PAGE_READWRITE, &dwprotect);
            if(bRet == FALSE)   {   return FALSE;   }
            bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, (LPVOID)&memValue, sizeof(FLOAT), &nReadSize);
            if(bRet == FALSE)
            {
                ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(FLOAT), dwprotect, 0);
                return  FALSE;
            }
            ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(FLOAT), dwprotect, 0);

            return memValue == findValue;
        }
        break;
    case 4://DOUBLE
        {
            DOUBLE findValue, memValue ;
            findValue = (DOUBLE)atof(findtext);
            if(findValue == 0)      {   return FALSE;   }
            bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(DOUBLE), PAGE_READWRITE, &dwprotect);
            if(bRet == FALSE)   {   return FALSE;   }
            bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, (LPVOID)&memValue, sizeof(DOUBLE), &nReadSize);
            if(bRet == FALSE)
            {
                ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(DOUBLE), dwprotect, 0);
                return  FALSE;
            }
            ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, sizeof(DOUBLE), dwprotect, 0);

            return memValue == findValue;
        }
        break;
    case 5://String
        {   
            nReadSize = strlen(findtext);
            TCHAR szBuffer[MAX_PATH] = {0};
            bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, nReadSize, PAGE_READWRITE, &dwprotect);
            if(bRet == FALSE)   {   return FALSE;   }
            bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, szBuffer, nReadSize, 0);
            if(bRet == FALSE)
            {
                ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, nReadSize, dwprotect, 0);
                return  FALSE;
            }
            ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, nReadSize, dwprotect, 0);

            return Compare(findtext, szBuffer, nReadSize);;
        }
        break;
    }
    return FALSE;
}

// -----------------------------------------------------------//
// Function:    WriteBuffer
// Param        HANDLE          hProcess    �i��
//              DWORD           dwAddr      �n��
//              LPCTSTR         buffer      �ɝ�
//              UINT            nSize       �召
// Return  :    BOOL 
// meaning :    ���ɝ�
// -----------------------------------------------------------//
BOOL WriteBuffer(HANDLE hProcess, DWORD dwAddr, LPCTSTR buffer, UINT nSize)
{   
    if(hProcess == NULL)    
    {
        return FALSE;
    }
    DWORD dwprotect;
    BOOL bRet = FALSE;
    if(VirtualProtectEx(hProcess, (LPVOID)dwAddr, nSize, PAGE_READWRITE, &dwprotect))
    {
        if(WriteProcessMemory(hProcess, (LPVOID)dwAddr, buffer, nSize, 0))
        {
            bRet = TRUE;
        }
        VirtualProtectEx(hProcess, (LPVOID)dwAddr, nSize, dwprotect, &dwprotect);
        bRet = FlushInstructionCache(hProcess, (LPVOID)dwAddr, nSize);
    }

    return bRet;
}

// -----------------------------------------------------------//
// Function:    Compare
// Param        LPCTSTR         szSrc       ��
//              LPCTSTR         szSrc2      �ڕW
//              UINT            nLen        ���x
// Return  :    BOOL 
// meaning :    ��r������ 
// -----------------------------------------------------------//
BOOL Compare(LPCTSTR szSrc, LPCTSTR szSrc2, UINT nLen)
{
    int nCount = 0;
    for(UINT i = 0; i < nLen; i++)
    {
        if(szSrc[i] == szSrc2[i])
        {
            nCount++;
        }
    }
    return nCount == nLen;
}

// -----------------------------------------------------------//
// Function:    ReadMemory
// Param        HANDLE              hProcess
//              DWORD               dwAddrBase
//              int                 flag
//              LPCTSTR             findtext
//              LPCTSTR             findtext
//              CArray<int, int>&   indexArr
// Return  :    void 
// meaning :    
// -----------------------------------------------------------//
void ReadMemory(HANDLE hProcess, DWORD dwAddrBase, int flag, LPCTSTR findtext, CArray<int, int>& indexArr)
{   
    indexArr.RemoveAll();
    BOOL bRet = FALSE;
    TCHAR szBuffer[PAGE_SIZE] = {0};
    memset(szBuffer, 0x00, PAGE_SIZE);
    DWORD dwprotect;
    SIZE_T nReadSize;

    // 1:椎�����ɝ�
    bRet = ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, PAGE_SIZE, PAGE_READWRITE, &dwprotect);
    if(bRet == FALSE)
    {
        return;
    }
    bRet = ::ReadProcessMemory(hProcess, (LPVOID)dwAddrBase, szBuffer, PAGE_SIZE, &nReadSize);
    if(bRet == FALSE)
    {
        ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, PAGE_SIZE, dwprotect, 0);
        return;
    }
    ::VirtualProtectEx(hProcess, (LPVOID)dwAddrBase, PAGE_SIZE, dwprotect, 0);
    // 2:�ɝ���r�l��n���Έڗ�
    switch(flag)
    {
    case 0: // BYTE
        {
            BYTE value;
            value = (BYTE)atoi(findtext);
            if(value != 0)
                FindByte(szBuffer, value, PAGE_SIZE, indexArr);
        }
        break;
    case 1: // SHORT
        {
            SHORT value;
            value = (SHORT)atoi(findtext);
            if(value != 0)
                FindSHORT(szBuffer, value, PAGE_SIZE, indexArr);
        }
        break;
    case 2: // INT
        {
            INT value;
            value = (INT)atoi(findtext);
            if(value != 0)
                FindINT(szBuffer, value, PAGE_SIZE, indexArr);
        }
        break;
    case 3: //FLOAT
        {
            FLOAT value;
            value = (FLOAT)atof(findtext);
            if(value != 0)
                FindFLOAT(szBuffer, value, PAGE_SIZE, indexArr);
        }
        break;
    case 4: //DOUBLE
        {
            DOUBLE value;
            value = atof(findtext);
            if(value != 0)
                FindDOUBLE(szBuffer, value, PAGE_SIZE, indexArr);
        }
        break;
    case 5: // ������
        { 
            FindStr(szBuffer, findtext, PAGE_SIZE, indexArr);
        }
        break;   
    }
}

// -----------------------------------------------------------//
// Function:    FindByte
// Param        LPCTSTR        szSrc
//              LPCTSTR        szFind
//              UINT        nSize
//              UINT        nSize
//              int>&        indexArr
// Return  :    void 
// meaning :    �r��BYTE
// -----------------------------------------------------------//
void FindByte(LPCTSTR szSrc, BYTE byteData, UINT nSize, CArray<int, int>& indexArr)
{
    UINT index = 0;
    while(index < nSize)
    {
        BYTE b = (BYTE)szSrc[index];
        if(b == byteData)
        {
            indexArr.Add(index);
        }
        index++;
    }
}

// -----------------------------------------------------------//
// Function:    FindSHORT
// Param        LPCTSTR             szSrc
//              SHORT               shortData
//              UINT                nSize
//              UINT                nSize
//              CArray<int, int>&   indexArr
// Return  :    void 
// meaning :    �r��SHORT 
// -----------------------------------------------------------//
typedef union tag_DATA_SHORT
{
    BYTE bValue[4];
    INT intValue;
}DATA_SHORT;
void FindSHORT(LPCTSTR szSrc, SHORT shortData, UINT nSize, CArray<int, int>& indexArr)
{
    UINT index = 0;
    DATA_SHORT data;
    data.intValue = shortData;
    BYTE b1 = data.bValue[0];
    BYTE b2 = data.bValue[1];

    while(index < nSize - 1)
    {
        BYTE value1 = (BYTE)szSrc[index];
        BYTE value2 = (BYTE)szSrc[index+1];
        if(value1 == b1 && value2 == b2)
        {
            indexArr.Add(index);
            index += 1;
        }
        index++;
    }
}

// -----------------------------------------------------------//
// Function:    FindINT
// Param        LPCTSTR             szSrc
//              INT                 intData
//              UINT                nSize
//              UINT                nSize
//              CArray<int, int>&   indexArr
// Return  :    void 
// meaning :    �r��INT
// -----------------------------------------------------------//
typedef union tag_DATA_INT
{
    BYTE bValue[4];
    INT intValue;
}DATA_INT;
void FindINT(LPCTSTR szSrc, INT intData, UINT nSize, CArray<int, int>& indexArr)
{
    UINT index = 0;
    DATA_INT data;
    data.intValue = intData;
    BYTE b1 = data.bValue[0];
    BYTE b2 = data.bValue[1];
    BYTE b3 = data.bValue[2];
    BYTE b4 = data.bValue[3];

    while(index < nSize - 3)
    {
        BYTE value1 = (BYTE)szSrc[index];
        BYTE value2 = (BYTE)szSrc[index+1];
        BYTE value3 = (BYTE)szSrc[index+2];
        BYTE value4 = (BYTE)szSrc[index+3];
        if(value1 == b1 && value2 == b2 && value3 == b3 && value4 == b4)
        {
            indexArr.Add(index);
            index += 3;
        }
        index++;
    } 
}

// -----------------------------------------------------------//
// Function:    FindDOUBLE
// Param        LPCTSTR             szSrc
//              DOUBLE              doubleData
//              UINT                nSize
//              UINT                nSize
//              CArray<int, int>&   indexArr
// Return  :    void 
// meaning :    �r��FLOAT
// -----------------------------------------------------------//
typedef union tag_DATA_FLOAT
{
    BYTE bvalue[4];
    float fvalue;
}DATA_FLOAT;
void FindFLOAT(LPCTSTR szSrc, float floatData, UINT nSize, CArray<int, int>& indexArr)
{
    UINT index = 0;

    DATA_FLOAT data;
    data.fvalue = floatData;
    BYTE b1 = data.bvalue[0];
    BYTE b2 = data.bvalue[1];
    BYTE b3 = data.bvalue[2];
    BYTE b4 = data.bvalue[3];
    while(index < nSize - 3)
    {
        BYTE value1 = (BYTE)szSrc[index];
        BYTE value2 = (BYTE)szSrc[index+1];
        BYTE value3 = (BYTE)szSrc[index+2];
        BYTE value4 = (BYTE)szSrc[index+3];
        if(value1 == b1 && value2 == b2 && value3 == b3 && value4 == b4)
        {
            indexArr.Add(index);
            index += 3;
        }
        index++;
    } 
}

// -----------------------------------------------------------//
// Function:    FindDOUBLE
// Param        LPCTSTR             szSrc
//              DOUBLE              doubleData
//              UINT                nSize
//              UINT                nSize
//              CArray<int, int>&   indexArr
// Return  :    void 
// meaning :    �r��DOUBLE
// -----------------------------------------------------------//
typedef union tag_DATA_DOUBLE
{
    BYTE bvalue[8];
    DOUBLE fvalue;
}DATA_DOUBLE;
void FindDOUBLE(LPCTSTR szSrc, DOUBLE doubleData, UINT nSize, CArray<int, int>& indexArr)
{
    UINT index = 0;

    DATA_DOUBLE data;
    data.fvalue = doubleData;
    BYTE b1 = data.bvalue[0];
    BYTE b2 = data.bvalue[1];
    BYTE b3 = data.bvalue[2];
    BYTE b4 = data.bvalue[3];
    BYTE b5 = data.bvalue[4];
    BYTE b6 = data.bvalue[5];
    BYTE b7 = data.bvalue[6];
    BYTE b8 = data.bvalue[7];
    while(index < nSize - 3)
    {
        BYTE value1 = (BYTE)szSrc[index];
        BYTE value2 = (BYTE)szSrc[index+1];
        BYTE value3 = (BYTE)szSrc[index+2];
        BYTE value4 = (BYTE)szSrc[index+3];
        BYTE value5 = (BYTE)szSrc[index+4];
        BYTE value6 = (BYTE)szSrc[index+5];
        BYTE value7 = (BYTE)szSrc[index+6];
        BYTE value8 = (BYTE)szSrc[index+7];
        if(value1 == b1 && value2 == b2 && value3 == b3 && value4 == b4 &&
            value5 == b5 && value6 == b6 && value7 == b7 && value8 == b8)
        {
            indexArr.Add(index);
            index += 7;
        }
        index++;
    } 
}

// -----------------------------------------------------------//
// Function:    FindStr
// Param        LPCTSTR             szSrc
//              LPCTSTR             szFind
//              UINT                nSize
//              CArray<int, int>&   indexArr
// Return  :    void 
// meaning :    ��r������
// -----------------------------------------------------------//
void FindStr(LPCTSTR szSrc, LPCTSTR szFind, UINT nSize, CArray<int, int>& indexArr)
{
    if(szSrc == NULL || szFind == 0)    return;

    UINT index = 0;
    int nLen = (int)strlen(szFind);

    while(index < nSize)
    {
        if(szSrc[index] == szFind[0])
        {
            if(Compare(szSrc+index, szFind, nLen))
            {
                indexArr.Add(index);
            }
            else
            {
                index += nLen - 1;
            }
        }
        index++;
    }
}

// -----------------------------------------------------------//
// Function:    SearchMemoryAddress
// Param        HANDLE              hProcess        [in]�i��
//              int                 flag            [in]�ɝ��ތ^
//              LPCTSTR             findtext        [in]�ɝ�
//              CArray<int, int>&   dwAddrArr       [out]�n���W��
// Return  :    void 
// meaning :    �r���i���ɝ��n���W��
// -----------------------------------------------------------//
void SearchMemoryAddress(HANDLE hProcess, int flag, LPCTSTR findtext, CArray<DWORD, DWORD>& dwAddrArr)
{   
    g_IsSearching = TRUE;

    DWORD dwAddrBase = ADDRESS_BEGIN;
    DWORD dwReadSize = 0;
    BOOL bRet = FALSE;
    CArray<int, int> indexArr;

    if(g_bFirstSerach)  // ��ꎟ
    {
        dwAddrArr.RemoveAll();
        while(dwAddrBase < ADDRESS_END)
        {
            ReadMemory(hProcess, dwAddrBase, flag, findtext, indexArr);
            for(int i = 0; i < indexArr.GetCount(); i++)
            {
                DWORD dwAddress = dwAddrBase + indexArr.GetAt(i);   // BaseAddr + �Έڗ�
                dwAddrArr.Add(dwAddress);
            }

            dwAddrBase += PAGE_SIZE;
        }
        g_bFirstSerach = FALSE;
    }
    else
    {
        int nCount = dwAddrArr.GetCount();
        for(int i = 0; i < nCount; i++)
        {
            DWORD dwAddr = dwAddrArr.GetAt(i);
            // �w������ɝ��o�c�O�ɝ����ەC�z
            if(BoolMemoryDataIsOK(hProcess, dwAddr, flag, findtext) == FALSE)
            {
                dwAddrArr.RemoveAt(i);
                i--;
                nCount--;
            }
        }
    }

    g_IsSearching = FALSE;
    g_Thead = NULL;

    // ᢑ�����
    ::SendMessage(m_ParentHwnd, SEARCH_MSG, 0, 0);
}

// -----------------------------------------------------------//
// Function:    GetProcessInfo
// Param                
//              PROCESSENTRY32&>&        processList
// Return  :    void 
// meaning :    �i��exe�r������
// -----------------------------------------------------------//
void FlushProcessInfo(CArray<PROCESSENTRY32_, PROCESSENTRY32_>& processList)
{
    PROCESSENTRY32_ entry;
    memset(&entry, 0x00, sizeof(PROCESSENTRY32_));
    entry.dwSize = sizeof(PROCESSENTRY32_);
    BOOL bRet = FALSE;

    // �n��Process����
    HANDLE hSnapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hSnapShot == NULL)
    {
        return;
    }
    bRet = ::Process32First(hSnapShot, (PROCESSENTRY32*)&entry);
    while(bRet)
    {
        // AddNew
        processList.Add(entry);
        // MoveNext
        bRet = ::Process32Next(hSnapShot, (PROCESSENTRY32*)&entry);
    }
}

///////////////////////////////////////////////////////////////////
// Message
void SetParentHwnd(HWND hwnd)
{
    m_ParentHwnd = hwnd;
}