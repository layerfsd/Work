//*-----------------------------------------------------------------------------*/
//* Copyright(C) 2014, liujiquan Company All rights reserved. )
//* FileName :   CyberxEncrypt.cpp
//* Author   :   liujiquan
//* DateTime :   12/10/2014
//* Version  :   1.0
//* Comment  :   
//*-----------------------------------------------------------------------------*/
#include "CyberxEncrypt.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const unsigned short	g_nMaxLen = 2048;		//
const unsigned short	g_nMask = 0x07FF;		//
unsigned char g_szKeyData[] = 
{
	0x83,0x04,0x89,0x44,0x56,0x66,0xDF,0x24,0xE6,0x54,0x9A,0x3B,0x16,0x36,0x08,0x42,
	0x6B,0x56,0x4A,0x31,0x88,0x56,0x6B,0x0B,0x5C,0x6C,0x6A,0x42,0x8E,0x2E,0x6F,0x54,
	0x54,0x44,0xBD,0x2E,0x27,0x65,0x24,0x35,0xF0,0x2E,0xF5,0x79,0x96,0x4E,0xD6,0x52,
	0x1E,0x16,0xDE,0x18,0xC1,0x34,0xE2,0x16,0x98,0x28,0xDA,0x7E,0xD7,0x7E,0xC8,0x47,
	0xAB,0x5E,0x8D,0x1F,0x35,0x7C,0x82,0x38,0x3D,0x3C,0xD9,0x38,0x8B,0x56,0x14,0x02,
	0x0E,0x74,0x0D,0x79,0x3A,0x6F,0x65,0x7B,0x3E,0x50,0x59,0x55,0x01,0x2C,0x4D,0x63,
	0x10,0x04,0x86,0x24,0xD9,0x76,0xEF,0x70,0xED,0x4A,0xE3,0x51,0x1D,0x75,0x49,0x3E,
	0xAC,0x78,
};
/////////////////////////////////////////////////////////
// �o�C�i�� �e�L�X�g�ϊ�

DWORD MfxMemToSting(CString& strString, LPCTSTR lpszMem, DWORD dwSize)
{
	LPTSTR pszT = strString.GetBuffer(dwSize * 2);

	for (DWORD i = 0; i < dwSize; i++)
	{
		sprintf(pszT, "%02X", (BYTE)*lpszMem);
		pszT += 2;
		lpszMem++;
	}
	*pszT = 0;
	strString.ReleaseBuffer();

	return dwSize * 2;
}

void MfxAddString(CString& strString,  LPCTSTR lpvSrc, DWORD dwSize)
{
	CString strT;
	MfxMemToSting(strT, lpvSrc, dwSize);
	strString += strT;
}

/////////////////////////////////////////////////////////
// �e�L�X�g �o�C�i���ϊ�

void MfxStingToMem(LPTSTR lpszMem, LPCTSTR lpszString)
{
	LPCTSTR pszT = lpszString;

	while (*pszT != NULL)
	{
		*lpszMem = 0;
		for (int j = 1; j >= 0; j--)
		{
			*lpszMem += (*pszT <= '9') ? (*pszT - '0') << (4 * j) : (*pszT - 'A' + 10) << (4 * j);
			pszT++;
		}
		lpszMem++;
	}
}

///////////////////////////////////////////////////////////////////////////////////
// �Í����̐���

CString Encryption(LPCTSTR lpszPlaintext, LPCTSTR lpvKeyData)
{
	unsigned short nRandomNo; 				//	�C�ӂ̗����l
	unsigned short nTableLen; 				//	��̃e�[�u���̑傫��
	unsigned short nSeed;
	//	�o�b�t�@
	unsigned short* pD = new unsigned short[g_nMaxLen];
	unsigned short* pX = new unsigned short[g_nMaxLen];
	unsigned short* pY = new unsigned short[g_nMaxLen];
	unsigned short* pZ = new unsigned short[g_nMaxLen];
	unsigned long	m, n;
	short 			dsize;
	unsigned short	c, i, j, k, l, p, tmp;
	CString strCiphertext;

	int nRet = TRUE;


	//	�o�b�t�@�̎擾

	if (pD && pX && pY && pZ && lpvKeyData)
	{
		nTableLen = *(WORD*)lpvKeyData;			// �e�[�u����
		nRandomNo = *(WORD*)(lpvKeyData + 2);	// �����l
		memcpy(pZ, lpvKeyData + 4, 110);		// �����\���R�s�[

		srand((UINT)time(NULL));				//	�����̏�����

		//	��̃e�[�u���W�J

		m = ((unsigned long)rand()) << 16;
		m |= (unsigned long)rand();
		n = ((unsigned long)rand()) << 16;
		n |= (unsigned long)rand();
		i = (short)(m % (unsigned long)nTableLen);		//	��̃e�[�u���I�t�Z�b�g
		j = (short)(n % (unsigned long)nTableLen);		//	��̃e�[�u���I�t�Z�b�g

		if ( i > j )
			k = i;
		else
			k = j;										//	k �ɑ傫����������

		if (k >= 55)
		{
			for (c = 55; c <= k; c++)
				pZ[c] = pZ[c-24] - pZ[c-55];			//	��̃e�[�u����W�J
		}

		//	������̏�����

		nSeed = pZ[i];									//	������o��
		pX[55] = nSeed;
		tmp = 1;
		for ( i = 1; i < 55; i++ )						//	�������ł΂�܂�
		{
			p = ( i * 21 ) % 55;
			pX[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pX[p];
		}
		for (i = 56; i < 256; i++) 						//	���������܂��Ă���
			pX[i] = pX[i - 24] - pX[i - 55];
		for (i = 0; i < 55; i++ )						//	�l���T�T�擪�փR�s�[
			pX[i] = pX[i + 200];

		nSeed = pZ[j];									//	������o��
		pY[55] = nSeed;
		tmp = 1;
		for (i = 1; i < 55; i++)						//	�������ł΂�܂�
		{
			p = ( i * 21 ) % 55;
			pY[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pY[p];
		}
		for (i = 56; i < 256; i++) 						//	���������܂��Ă���
			pY[i] = pY[i - 24] - pY[i - 55];
		for (i = 0; i < 55; i++)						//	�l���T�T�擪�փR�s�[
			pY[i] = pY[i + 200];

		//	�Í����O�̏�����
		i = 55;
		j = 55;
		l = 0;
		k = 1;
		pD[0] = nRandomNo;

		//	�Í���

		MfxAddString(strCiphertext, (char*)&m, sizeof(DWORD));		//	m �̏o��
		MfxAddString(strCiphertext, (char*)&n, sizeof(DWORD));		//	n �̏o��

		WORD nLen = g_nMaxLen * 2 - 2;
		while (*lpszPlaintext != NULL)
		{												//	������ǂݍ���
			dsize = min(strlen(lpszPlaintext), nLen);
			strncpy(((char*)pD) + 2, lpszPlaintext, nLen);
			lpszPlaintext += dsize;

			dsize = (dsize + 1) / 2;					//	�o�C�g�̔��[�͐؂�グ�Ă���
			dsize += 1; 								//	�擪�ɓ����p�^�[����
			for (k = 1; k < dsize; i++, j++, l++, k++)
			{											//	�o�b�t�@�����E���h����悤�Ƀ}�X�N
				pX[i & g_nMask] = pX[(i - 24) & g_nMask] - pX[(i - 55) & g_nMask] - pD[k - 1];
				pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
				while ((pX[i & g_nMask] + pY[j & g_nMask]) == 0)
				{										// �������ۏo���ɂȂ�Ȃ��悤
					j++;
					pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
				}
				pZ[l] = (pX[i & g_nMask] + pY[j & g_nMask]) ^ pD[k];
			}
			MfxAddString(strCiphertext, (char*)pZ, (dsize - 1) * 2);	//	�Í����̏o��

			pD[0] = pD[dsize - 1];						//	�o�͂����������o�b�t�@�擪��
			k = 1;										//	���̕����J�n�ʒu
			l = 0;										//	�Í����o�b�t�@�擪�փZ�b�g
		}
	}

	if (pD)
		delete pD;
	if (pX)
		delete pX;
	if (pY)
		delete pY;
	if (pZ)
		delete pZ;

	return strCiphertext;
}


///////////////////////////////////////////////////////////////////////////////////
// �����̐���

CString Decryption(LPCTSTR lpszCiphertext, LPCTSTR lpvKeyData)
{
	unsigned short	nRandomNo; 				//	�C�ӂ̗����l
	unsigned short	nTableLen; 				//	��̃e�[�u���̑傫��
	unsigned short	nSeed;
	unsigned long	m, n;
	short 			dsize;
	unsigned short	c, i, j, k, l, p, tmp;
	CString strPlaintext = _T("");
	short nCiphertextLen = strlen(lpszCiphertext) / 2;

	if (nCiphertextLen < 8)
		return strPlaintext;

	//	�o�b�t�@�̎擾
	unsigned short* pD = new unsigned short[g_nMaxLen];
	unsigned short* pX = new unsigned short[g_nMaxLen];
	unsigned short* pY = new unsigned short[g_nMaxLen];
	unsigned short* pZ = new unsigned short[g_nMaxLen];
	unsigned char* pC = new unsigned char[nCiphertextLen];

	if (pD && pX && pY && pZ && pC && lpvKeyData)
	{
		nTableLen = *(WORD*)lpvKeyData;			// �e�[�u����
		nRandomNo = *(WORD*)(lpvKeyData + 2);	// �����l
		memcpy(pZ, lpvKeyData + 4, 110);		// �����\���R�s�[

		MfxStingToMem((LPTSTR)pC, lpszCiphertext);

		m = *(DWORD*)pC; 		//	m �̓ǂ݂Ƃ�
		n = *(DWORD*)(pC + 4); 	//	n �̓ǂ݂Ƃ�

		//	��̃e�[�u���W�J

		i = (short)(m % (unsigned long)nTableLen);			//	��̃e�[�u���I�t�Z�b�g
		j = (short)(n % (unsigned long)nTableLen);			//	��̃e�[�u���I�t�Z�b�g

		k = (i > j) ? i : j;								//	k �ɑ傫����������
		if (k >= 55)
		{
			for (c = 55; c <= k; c++)
				pZ[c] = pZ[c - 24] - pZ[c - 55];			//	��̃e�[�u����W�J
		}

		//	������̏�����

		nSeed = pZ[i];										//	������o��
		pX[55] = nSeed;
		tmp = 1;
		for (i = 1; i < 55; i++)							//	�������ł΂�܂�
		{
			p = ( i * 21 ) % 55;
			pX[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pX[p];
		}
		for (i = 56; i < 256; i++) 							//	���������܂��Ă���
			pX[i] = pX[i - 24] - pX[i - 55];
		for (i = 0; i < 55; i++)							//	�l���T�T�擪�փR�s�[
			pX[i] = pX[i + 200];

		nSeed = pZ[j];										//	������o��
		pY[55] = nSeed;
		tmp = 1;
		for (i = 1; i < 55; i++)							//	�������ł΂�܂�
		{
			p = ( i * 21 ) % 55;
			pY[p] = tmp;
			tmp = nSeed - tmp;
			nSeed = pY[p];
		}
		for (i = 56; i < 256; i++) 							//	���������܂��Ă���
			pY[i] = pY[i - 24] - pY[i - 55];
		for (i = 0; i < 55; i++)							//	�l���T�T�擪�փR�s�[
			pY[i] = pY[i + 200];

		//	�������O�̏�����

		i = 55;
		j = 55;
		l = 0;
		k = 1;
		pD[0] = nRandomNo;

		//	������

		nCiphertextLen -= 8;
		int nRead = 8;

		while ((dsize = min(g_nMaxLen * 2 - 2, nCiphertextLen)) != 0)
		{													//	�Í���ǂݍ���
			memcpy(pZ, pC + nRead, dsize);
			nRead += dsize;
			nCiphertextLen -= dsize;

			dsize /= 2; 									//	���[�h�T�C�Y�ɒ���
			dsize += 1; 									//	�擪�ɓ����p�^�[����
			for (k = 1; k < dsize; i++, j++, l++, k++)
			{												//	�o�b�t�@�����E���h����悤�Ƀ}�X�N
				pX[i & g_nMask] = pX[(i - 24) & g_nMask] - pX[(i - 55) & g_nMask] - pD[k - 1];
				pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
				short ss1 = pX[i & g_nMask];
				short ss2 = pY[j & g_nMask];
				short ss3;
				while ((pX[i & g_nMask] + pY[j & g_nMask]) == 0)
				{											// �������ۏo���ɂȂ�Ȃ��悤
					j++;
					pY[j & g_nMask] = pY[(j - 24) & g_nMask] - pY[(j - 55) & g_nMask];
					ss3 = pY[j & g_nMask];
				}
				unsigned short  u1 = pX[i & g_nMask];
				unsigned short u2 = pY[j & g_nMask];
				unsigned short u3 = u1 + u2;
				unsigned short u4 = pZ[l];
				unsigned short u5 = u3 ^ u4;
				pD[k] = (pX[i & g_nMask] + pY[j & g_nMask]) ^ pZ[l];
			}
			*((char*)pD + (dsize - 1) * 2 + 2) = 0;
			strPlaintext += ((char*)pD) + 2;				//	�����̏o��

			pD[0] = pD[dsize - 1];							//	�o�͂����������o�b�t�@�擪��
			k = 1;											//	���̕����J�n�ʒu
			l = 0;											//	�Í����o�b�t�@�擪�փZ�b�g
		}
	}

	if (pD)
		delete pD;
	if (pX)
		delete pX;
	if (pY)
		delete pY;
	if (pZ)
		delete pZ;
	if (pC)
		delete pC;

	return strPlaintext;
}
