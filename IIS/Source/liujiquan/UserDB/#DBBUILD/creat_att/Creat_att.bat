@echo on
:**********************************************************************
:*       テーブルクリエイト　バッチファイル 　　　　　　　　　　　    *
:*                                                                    *
:*   DATE   : 2013-04-10   謝険峰	                              *
:*   LastUpdate:                                                      *
:**********************************************************************

     if "%1" == "" goto error
     if "%2" == "" goto error


	call crtb DADAYIDF_TBL.SQL %1 %2 %3 %4

	goto END_PROC
:error
echo ****************************************************************************
echo *                                                                          *
echo *  %1= "ServerName"  %2= "UserName"  %3= "Password"   %4= "DataBase"       *
echo *                                                                          *
echo ****************************************************************************
:END_PROC
