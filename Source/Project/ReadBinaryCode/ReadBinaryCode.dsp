# Microsoft Developer Studio Project File - Name="ReadBinaryCode" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ReadBinaryCode - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ReadBinaryCode.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ReadBinaryCode.mak" CFG="ReadBinaryCode - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ReadBinaryCode - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ReadBinaryCode - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ReadBinaryCode - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# Begin Custom Build
TargetName=ReadBinaryCode
InputPath=.\Release\ReadBinaryCode.exe
SOURCE="$(InputPath)"

"..\Bin\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Release\$(TargetName).exe  ..\Bin

# End Custom Build

!ELSEIF  "$(CFG)" == "ReadBinaryCode - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Custom Build
TargetName=ReadBinaryCode
InputPath=.\Debug\ReadBinaryCode.exe
SOURCE="$(InputPath)"

"..\Bin_debug\$(TargetName).exe" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy Debug\$(TargetName).exe  ..\Bin_debug

# End Custom Build

!ENDIF 

# Begin Target

# Name "ReadBinaryCode - Win32 Release"
# Name "ReadBinaryCode - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ProcessInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadBinaryCode.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadBinaryCode.rc
# End Source File
# Begin Source File

SOURCE=.\ReadBinaryCodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ProcessInfo.h
# End Source File
# Begin Source File

SOURCE=.\ReadBinaryCode.h
# End Source File
# Begin Source File

SOURCE=.\ReadBinaryCodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ReadBinaryCode.ico
# End Source File
# Begin Source File

SOURCE=.\res\ReadBinaryCode.rc2
# End Source File
# End Group
# Begin Group "Util"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AccembFindDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AccembFindDlg.h
# End Source File
# Begin Source File

SOURCE=.\AssemblyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AssemblyDlg.h
# End Source File
# Begin Source File

SOURCE=.\AssemGotoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AssemGotoDlg.h
# End Source File
# Begin Source File

SOURCE=.\DropFileEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DropFileEdit.h
# End Source File
# Begin Source File

SOURCE=.\PEUtil.cpp

!IF  "$(CFG)" == "ReadBinaryCode - Win32 Release"

!ELSEIF  "$(CFG)" == "ReadBinaryCode - Win32 Debug"

# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\PEUtil.h
# End Source File
# Begin Source File

SOURCE=.\Psapi.h
# End Source File
# End Group
# Begin Group "ntdll"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ntdll.h
# End Source File
# Begin Source File

SOURCE=.\ntdll_interface.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\ntdll_interface.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ndisasm.exe
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
