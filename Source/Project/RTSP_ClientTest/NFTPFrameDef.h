/************************************************************************
*
*	Copyrite (c) ����ŵ����Ѷ�Ƽ��������޹�˾�з���
*	All rights reserved.
*
*	NFTPFrameDef.h
*	����NFTP֡����
*
*	v0.1
*	Wen Ming, Li Yongbin
*	2005-6-28
*
************************************************************************/

#ifndef __NFTP_FRAME_DEF_H__
#define __NFTP_FRAME_DEF_H__

#define NFTP_STARTCODE 0x4E465450

/********************************************************************************************
*
* ע�⣺
*
*	1. ���ڱ������Ĳ�ͬ�п�����ɶ�������ݽṹ�Ͷ�Ӧ������ͼ����Ӧ����ʱ��������ͼ�ĽṹΪ׼��
*
*	2. ���нṹ�嶨���ֶ�ȫΪ������(��ͷ��)��
*
*********************************************************************************************/


/******************************************************************
*
*   ͨ������֡��ʽ      �ͻ��� ��> �����
*
*                      32 bit
*   ____________|____________|_____________|____________|
*  |		    	start code (NFTP)                   |
*  |____________________________________________________|
*  |			reserve		  |        frame length     |
*  |__________________________|_________________________|
*  |			    	  command						|
*  |____________________________________________________|
*
*	������������֡����ͨ������֡��ʽ
*	fram length = 12
*
*****************************************************************/

typedef struct tagNFTPGenCommFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
} NFTP_GEN_COMM, *pNFTP_GEN_COMM;


/******************************************************************
*
*   ����������֡��ʽ       �ͻ��� ��> �����
*
*                      32 bit
*   ____________|____________|_____________|____________|
*  |		    	start code (NFTP)                   |
*  |____________________________________________________|
*  |			type		  |        frame length     |
*  |__________________________|_________________________|
*  |			    	  command						|
*  |____________________________________________________|
*  |                      parameter                     |
*  |____________________________________________________|
*
*	frame length Ϊʵ��֡���ȣ�������start code��
*
*****************************************************************/
typedef struct tagNFTPDiskPara  
{
	unsigned int 	dev_id;
	unsigned int 	partition_id;
	char			filename[64];
	unsigned int  	offset;
	unsigned int  	len;
	char 			dir[64];	
}NFTPDiskPara,*pNFTPDiskPara;


typedef struct tagNFTPUserFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
	char			username[64];
} NFTP_USER_COMM, *pNFTP_USER_COMM;

typedef struct tagNFTPPassFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
	char			password[64];
} NFTP_PASS_COMM, *pNFTP_PASS_COMM; 

typedef struct tagNFTPDownFrame  
{
	unsigned int 	startCode;
	unsigned short	reserve;
	unsigned short  frameLen;
	char			comm[4];
	NFTPDiskPara    para;
} NFTP_PARA_COMM, *pNFTP_PARA_COMM;

/******************************************************************
*
*   �ظ�֡ͨ�ø�ʽ		����� -> �ͻ���
*
*							32 bit
*   ____________|_____________|_____________|___________|
*  |		    	start code (NFTP)                   |
*  |____________________________________________________|
*  | reply code |frm len high |    frame length low     |
*  |__________________________|_________________________|
*  |                       data                         |
*  |____________________________________________________|
*
*
*
*
*****************************************************************/

//��ͨ�ظ�
//frmLenH = 0, frmLenL = 8
typedef struct  tagNFTPCommonReply
{
	unsigned int 	startCode;
	unsigned char   replyCode;
	unsigned char	frmLenH;
	unsigned short	frmLenL;
} NFTP_COMMON_REPLY, *pNFTP_COMMON_REPLY;


//���ݻظ�
typedef struct  tagNFTPDataReply
{
	unsigned int 	startCode;
	unsigned char   replyCode;
	unsigned char	frmLenH;
	unsigned short	frmLenL;
	unsigned char	data[4];
} NFTP_DATA_REPLY, *pNFTP_DATA_REPLY;

//�ظ����붨�� (reply code):
#define COMMAND_OK				60 
#define COMMAND_FAIL			61		
#define INVALID_COMMAND			62
#define INVALID_PARAMETER		63
#define SERVICE_READY			64	
#define SERVICE_NOOP			65	
#define SERVICE_ABORT			66	
#define SERVICE_CLOSE			67	
#define SERVICE_FULL			68	
#define SERVICE_BUSY			69
#define SERVICE_OVERTIME		70	
#define INVALID_ABORT			71


#define DLOG_FILE_READY			80
#define PLOG_FILE_READY			81
#define DOWN_FILE_READY			82
#define DLOG_FILE				83
#define PLOG_FILE				84
#define DOWN_FILE				85
#define DLOG_FILE_OVER			86
#define PLOG_FILE_OVER			87
#define DOWN_FILE_OVER			88
#define FILE_ERROR				89
#define ALL_FILE_OVER			90


#endif