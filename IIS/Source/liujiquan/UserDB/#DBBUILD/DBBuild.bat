@echo on
:**********************************************************************
:*       �e�[�u���Z�b�g�`�k�k    �o�b�`�t�@�C��  �@                   *
:*                                                                    *
:*   DATE   : 2013-04-03                                              *
:**********************************************************************
:

     if "%1" == "" goto error
     if "%2" == "" goto error

     CD colm_att
     CALL colm_att %1 %2 %3 %4

     CD ..\creat_att
     CALL Creat_att %1 %2 %3 %4

     CD ..\DGCUSTOM
     CALL DGCUSTOM %1 %2 %3 %4

     CD ..

     goto END_PROC

:error
echo **************************************************************************
echo *                                                               	      *
echo *  %1= "ServerName"  %2= "UserName"  %3= "Password"   %4= "DataBase"     *
echo *                                                               	      *
echo **************************************************************************
:END_PROC
