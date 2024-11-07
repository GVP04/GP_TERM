# Microsoft Developer Studio Project File - Name="GP_Term" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=GP_Term - Win32 DebugXP
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "GP_Term.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "GP_Term.mak" CFG="GP_Term - Win32 DebugXP"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "GP_Term - Win32 ReleaseNT" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 DebugNT" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZRelease95ENGL" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZReleaseNTENGL" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZRelease95" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZReleaseNT" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZRelease98" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZRelease2000" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZRelease2000ENGL" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZRelease98ENGL" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZReleaseXPENGL" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZReleaseXP" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 BRIZDebugXPENGL" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 DebugXP" (based on "Win32 (x86) Application")
!MESSAGE "GP_Term - Win32 ReleaseXP" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/GP_term", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseNT"
# PROP BASE Intermediate_Dir "ReleaseNT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseNT"
# PROP Intermediate_Dir "ReleaseNT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "W_NT" /D "MINFIN" /D "RUS" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "MINFIN" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugNT"
# PROP BASE Intermediate_Dir "DebugNT"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugNT"
# PROP Intermediate_Dir "DebugNT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "W_NT" /D "MINFIN" /D "RUS" /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Fr /Yu"stdafx.h" /J /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL" /d "MINFIN" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZRelease95ENGL"
# PROP BASE Intermediate_Dir "BRIZRelease95ENGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZRelease95ENGL"
# PROP Intermediate_Dir "BRIZRelease95ENGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /D "NDEBUG" /D "ENGL" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "W_95" /D "BRIZ" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease95ENGL/BRIZ.exe"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease95ENGL/BRIZ.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZReleaseNTENGL"
# PROP BASE Intermediate_Dir "BRIZReleaseNTENGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZReleaseNTENGL"
# PROP Intermediate_Dir "BRIZReleaseNTENGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /D "NDEBUG" /D "ENGL" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "W_NT" /D "BRIZ" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseNTENGL/BRIZ.exe"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseNTENGL/BRIZ.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZRelease95"
# PROP BASE Intermediate_Dir "BRIZRelease95"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZRelease95"
# PROP Intermediate_Dir "BRIZRelease95"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /D "NDEBUG" /D "RUS" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "W_95" /D "BRIZ" /D "RUS" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "BRIZRUS" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "BRIZRUS" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease95/BRIZ.exe"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease95/BRIZ.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZReleaseNT"
# PROP BASE Intermediate_Dir "BRIZReleaseNT"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZReleaseNT"
# PROP Intermediate_Dir "BRIZReleaseNT"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GR /GX /O2 /D "NDEBUG" /D "RUS" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "W_NT" /D "BRIZ" /D "RUS" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "BRIZRUS" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "BRIZRUS" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseNT/BRIZ.exe"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseNT/BRIZ.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZRelease98"
# PROP BASE Intermediate_Dir "BRIZRelease98"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZRelease98"
# PROP Intermediate_Dir "BRIZRelease98"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "RUS" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_98" /D "BRIZ" /D "RUS" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease98/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease98/BRIZ.exe"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZRelease2000"
# PROP BASE Intermediate_Dir "BRIZRelease2000"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZRelease2000"
# PROP Intermediate_Dir "BRIZRelease2000"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "RUS" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_2000" /D "BRIZ" /D "RUS" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease2000/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease2000/BRIZ.exe"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZRelease2000ENGL"
# PROP BASE Intermediate_Dir "BRIZRelease2000ENGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZRelease2000ENGL"
# PROP Intermediate_Dir "BRIZRelease2000ENGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "BRIZ" /D "ENGL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_2000" /D "BRIZ" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_AFXDLL" /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
# ADD RSC /l 0x409 /d "_AFXDLL" /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease2000ENGL/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease2000ENGL/BRIZ.exe"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZRelease98ENGL"
# PROP BASE Intermediate_Dir "BRIZRelease98ENGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZRelease98ENGL"
# PROP Intermediate_Dir "BRIZRelease98ENGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "BRIZ" /D "ENGL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_98" /D "BRIZ" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_AFXDLL" /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
# ADD RSC /l 0x409 /d "_AFXDLL" /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease98ENGL/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZRelease98ENGL/BRIZ.exe"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZReleaseXPENGL0"
# PROP BASE Intermediate_Dir "BRIZReleaseXPENGL0"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZReleaseXPENGL"
# PROP Intermediate_Dir "BRIZReleaseXPENGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "BRIZ" /D "ENGL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_XP" /D "BRIZ" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_AFXDLL" /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
# ADD RSC /l 0x409 /d "_AFXDLL" /d "NDEBUG" /d "BRIZENGL" /d "ENGLTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseXPENGL/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib UxTheme.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseXPENGL/BRIZ.exe"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BRIZReleaseXP"
# PROP BASE Intermediate_Dir "BRIZReleaseXP"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "BRIZReleaseXP"
# PROP Intermediate_Dir "BRIZReleaseXP"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "RUS" /D "BRIZ" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_XP" /D "BRIZ" /D "RUS" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseXP/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib UxTheme.lib /nologo /subsystem:windows /machine:I386 /out:"BRIZReleaseXP/BRIZ.exe"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BRIZDebugXPENGL"
# PROP BASE Intermediate_Dir "BRIZDebugXPENGL"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BRIZDebugXPENGL"
# PROP Intermediate_Dir "BRIZDebugXPENGL"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_AFXDLL" /D "BRIZ" /D "ENGL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Fr /Yu"stdafx.h" /J /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "W_XP" /D "BRIZ" /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Fr /Yu"stdafx.h" /J /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "BRIZENGL" /d "ENGLTABLE"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL" /d "BRIZENGL" /d "ENGLTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 gdiplus.lib winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"BRIZDebugXPENGL/BRIZ.exe" /pdbtype:sept
# ADD LINK32 gdiplus.lib winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib Secur32.lib UxTheme.lib /nologo /subsystem:windows /debug /machine:I386 /out:"BRIZDebugXPENGL/BRIZ.exe" /pdbtype:sept

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugXP"
# PROP BASE Intermediate_Dir "DebugXP"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugXP"
# PROP Intermediate_Dir "DebugXP"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_AFXDLL" /D "MINFIN" /D "RUS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Fr /Yu"stdafx.h" /J /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "W_2000" /D "MINFIN" /D "RUS" /D "_DEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Fr /Yu"stdafx.h" /J /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL" /d "MINFIN" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL" /d "MINFIN" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib UxTheme.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseXP"
# PROP BASE Intermediate_Dir "ReleaseXP"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseXP"
# PROP Intermediate_Dir "ReleaseXP"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "_AFXDLL" /D "RUS" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "W_2000" /D "MINFIN" /D "RUS" /D "NDEBUG" /D "_AFXDLL" /D "WIN32" /D "_WINDOWS" /D _WIN32_WINNT=0x600 /D _WIN32_IE=0x0700 /D "_MBCS" /D "SCI_LEXER" /D "SECURITY_WIN32" /Yu"stdafx.h" /J /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "BRIZRUS" /d "RUSTABLE"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL" /d "MINFIN" /d "RUSTABLE"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib /nologo /subsystem:windows /machine:I386 /out:"ReleaseXP/BRIZ.exe"
# ADD LINK32 winmm.lib htmlhelp.lib Vfw32.Lib imm32.lib Iphlpapi.lib gdiplus.lib Secur32.lib UxTheme.lib /nologo /subsystem:windows /machine:I386

!ENDIF 

# Begin Target

# Name "GP_Term - Win32 ReleaseNT"
# Name "GP_Term - Win32 DebugNT"
# Name "GP_Term - Win32 BRIZRelease95ENGL"
# Name "GP_Term - Win32 BRIZReleaseNTENGL"
# Name "GP_Term - Win32 BRIZRelease95"
# Name "GP_Term - Win32 BRIZReleaseNT"
# Name "GP_Term - Win32 BRIZRelease98"
# Name "GP_Term - Win32 BRIZRelease2000"
# Name "GP_Term - Win32 BRIZRelease2000ENGL"
# Name "GP_Term - Win32 BRIZRelease98ENGL"
# Name "GP_Term - Win32 BRIZReleaseXPENGL"
# Name "GP_Term - Win32 BRIZReleaseXP"
# Name "GP_Term - Win32 BRIZDebugXPENGL"
# Name "GP_Term - Win32 DebugXP"
# Name "GP_Term - Win32 ReleaseXP"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\scintilla\AutoComplete.cxx
# End Source File
# Begin Source File

SOURCE=.\AutoSizing.cpp
# End Source File
# Begin Source File

SOURCE=.\BrushExt.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\CallTip.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\CellBuffer.cxx
# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\COMImport.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\ComPortSetings.cpp
# End Source File
# Begin Source File

SOURCE=.\COMServer.cpp
# End Source File
# Begin Source File

SOURCE=.\Connector.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\ContractionState.cxx
# End Source File
# Begin Source File

SOURCE=.\DldTermcapVideo.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg_OLESet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgClienFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCodeco.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgContextMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateImageList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDelimiters.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDrawEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDumpSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditKeywords.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditorColor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditorPrintSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgErrors.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFileItemName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFontSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFontSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgGPScintillaFind.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGraphCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGUISet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGUISet.h
# End Source File
# Begin Source File

SOURCE=.\DlgImageList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImageMask.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInitComObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgKeyEditor.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewSession.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNewSpr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNotepadSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScreenSize.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSeparateView.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSeparateViewInFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetupSSH.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStatistics.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermcap.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapEsc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapEscLine.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapKbd.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapTerminal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTermSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewContextMenuMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewFSMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewInputAll.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewInputSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewIOFiles.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewItem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewOutputSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewRegMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgViewSystemMethods.cpp
# End Source File
# Begin Source File

SOURCE=.\DllImport.cpp
# End Source File
# Begin Source File

SOURCE=.\DllServer.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\Document.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\DocumentAccessor.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\Editor.cxx
# End Source File
# Begin Source File

SOURCE=.\EditorPrintSettings.cpp
# End Source File
# Begin Source File

SOURCE=.\ErrReport.cpp
# End Source File
# Begin Source File

SOURCE=.\excel8.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\ExternalLexer.cxx
# End Source File
# Begin Source File

SOURCE=.\FilterArray.cpp
# End Source File
# Begin Source File

SOURCE=.\FontExt.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_AutoSizing.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_comm.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_Control.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_DlgSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_File.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_HotKey.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_RarefiedArr.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_RTF.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_Term.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\GP_Term.hpj

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GP_Term.odl
# ADD MTL /h "GP_Term_i.h" /iid "GP_Term_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=.\GP_Term.rc
# End Source File
# Begin Source File

SOURCE=.\GP_TermDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_TermDoc2.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_TermView.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_termView2.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_termView3.cpp
# End Source File
# Begin Source File

SOURCE=.\GP_termView4.cpp
# End Source File
# Begin Source File

SOURCE=.\GPAdmIsOn.cpp
# End Source File
# Begin Source File

SOURCE=.\GPAniButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GPAnimate.cpp
# End Source File
# Begin Source File

SOURCE=.\GPAniStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\GPAsyncSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\GPBButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GPButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCDAODatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCDAOQueryDef.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCDAORecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCDAOTableDef.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCDAOWorkspace.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\GPChLBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GPColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GPComboBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GPComboBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCommonColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCommonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCommonFontDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GPContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\GPContainer.h
# End Source File
# Begin Source File

SOURCE=.\GPContextMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCurrent.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCursor.cpp
# End Source File
# Begin Source File

SOURCE=.\GPCursorArr.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDateTimeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgCommtype.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgFindReplace.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgNewValue.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgTelnetSet.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgViewMPVar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgViewSpr.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDlgViewSTable.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDrawWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GPDrLBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GPEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GPExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\GPFont.cpp
# End Source File
# Begin Source File

SOURCE=.\GPFontList.cpp
# End Source File
# Begin Source File

SOURCE=.\GPFrameBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPFrameWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\GPHandleArray.cpp
# End Source File
# Begin Source File

SOURCE=.\GPHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\GPHTMLDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\GPImageList.cpp
# End Source File
# Begin Source File

SOURCE=.\GPInputPool.cpp
# End Source File
# Begin Source File

SOURCE=.\GPIOFile.cpp
# End Source File
# Begin Source File

SOURCE=.\GPIOFileArray.cpp
# End Source File
# Begin Source File

SOURCE=.\GPLine.cpp
# End Source File
# Begin Source File

SOURCE=.\GPListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\GPListCtr.cpp
# End Source File
# Begin Source File

SOURCE=.\GPMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\GPMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\GPMonthCalCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\gpmsflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\GPNotifyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\GPObjDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GPODBC_Database.cpp
# End Source File
# Begin Source File

SOURCE=.\GPOleDispatchDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\GPOLEExcel1.cpp
# End Source File
# Begin Source File

SOURCE=.\gpolefont.cpp
# End Source File
# Begin Source File

SOURCE=.\GPOLERange.cpp
# End Source File
# Begin Source File

SOURCE=.\gppicture.cpp
# End Source File
# Begin Source File

SOURCE=.\GPProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\GPReBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPReBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GPRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\GPRegionArr.cpp
# End Source File
# Begin Source File

SOURCE=.\gprowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\GPScintilla.cpp
# End Source File
# Begin Source File

SOURCE=.\GPScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\GPScrollBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPScroller.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSlider.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSpinButton.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSpr.cpp
# End Source File
# Begin Source File

SOURCE=.\GPSprArray.cpp
# End Source File
# Begin Source File

SOURCE=.\GPStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\GPStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPStatusBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GPTabCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GPText.cpp
# End Source File
# Begin Source File

SOURCE=.\GPTextArray.cpp
# End Source File
# Begin Source File

SOURCE=.\GPTInterface.cpp
# End Source File
# Begin Source File

SOURCE=.\GPToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\GPToolBarCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GPToolTipCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\GPTree.cpp
# End Source File
# Begin Source File

SOURCE=.\GPUnit.cpp
# End Source File
# Begin Source File

SOURCE=.\GPViewInput.cpp
# End Source File
# Begin Source File

SOURCE=.\GPViewOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\GPwebbrowser2.cpp
# End Source File
# Begin Source File

SOURCE=.\GPWebBrowser2Sink.cpp
# End Source File
# Begin Source File

SOURCE=.\GPWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\GPWndPropertyArray.cpp
# End Source File
# Begin Source File

SOURCE=.\GPWndPropertyArrayItem.cpp
# End Source File
# Begin Source File

SOURCE=.\GPWndSizer.cpp
# End Source File
# Begin Source File

SOURCE=.\GPWndSizerArr.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\Indicator.cxx
# End Source File
# Begin Source File

SOURCE=.\IpFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\KeyMap.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\KeyWords.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexAda.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexAPDL.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexAsm.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexAsn1.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexAU3.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexAVE.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexBaan.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexBash.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexBasic.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexBullant.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexCaml.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexCLW.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexConf.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexCPP.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexCrontab.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexCSS.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexEiffel.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexErlang.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexEScript.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexForth.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexFortran.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexGui4Cli.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexHaskell.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexHTML.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexKix.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexLisp.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexLout.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexLua.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexMatlab.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexMetapost.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexMMIXAL.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexMPT.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexMSSQL.cxx
# End Source File
# Begin Source File

SOURCE=.\LexMVItem.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexNsis.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexOthers.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexPascal.cxx
# End Source File
# Begin Source File

SOURCE=.\LexPB.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexPerl.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexPOV.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexPowerB.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexPS.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexPython.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexRuby.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexScriptol.cxx
# End Source File
# Begin Source File

SOURCE=.\LexSepView.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexSpecman.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexSQL.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexTeX.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexVB.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexVerilog.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexVHDL.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LexYAML.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\LineMarker.cxx
# End Source File
# Begin Source File

SOURCE=.\ListMaker.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MemUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuCustom.cpp
# End Source File
# Begin Source File

SOURCE=.\MSFlexGridSink.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectGroupsArray.cpp
# End Source File
# Begin Source File

SOURCE=.\ODBCRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\ODContext.cpp
# End Source File
# Begin Source File

SOURCE=.\ODContextArray.cpp
# End Source File
# Begin Source File

SOURCE=.\PenExt.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\PlatWin.cxx
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\PropSet.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\RESearch.cxx
# End Source File
# Begin Source File

SOURCE=.\RgnExt.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\ScintillaBase.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\ScintillaWin.cxx
# End Source File
# Begin Source File

SOURCE=.\SendPickFlProgress.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\scintilla\Style.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\StyleContext.cxx
# End Source File
# Begin Source File

SOURCE=.\TableDataContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\TableDataContainerItem.cpp
# End Source File
# Begin Source File

SOURCE=.\TermCap.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\UniConversion.cxx
# End Source File
# Begin Source File

SOURCE=.\UniSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\ViewStyle.cxx
# End Source File
# Begin Source File

SOURCE=.\scintilla\WindowAccessor.cxx
# End Source File
# Begin Source File

SOURCE=.\WndPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\scintilla\XPM.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\scintilla\Accessor.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\AutoComplete.h
# End Source File
# Begin Source File

SOURCE=.\AutoSizing.h
# End Source File
# Begin Source File

SOURCE=.\BrushExt.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\CallTip.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\CellBuffer.h
# End Source File
# Begin Source File

SOURCE=.\CntrItem.h
# End Source File
# Begin Source File

SOURCE=.\COMImport.h
# End Source File
# Begin Source File

SOURCE=.\ComPortSetings.h
# End Source File
# Begin Source File

SOURCE=.\COMServer.h
# End Source File
# Begin Source File

SOURCE=.\Connector.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\ContractionState.h
# End Source File
# Begin Source File

SOURCE=.\DldTermcapVideo.h
# End Source File
# Begin Source File

SOURCE=.\Dlg_OLESet.h
# End Source File
# Begin Source File

SOURCE=.\DlgClienFiles.h
# End Source File
# Begin Source File

SOURCE=.\DlgCodeco.h
# End Source File
# Begin Source File

SOURCE=.\DlgContextMenu.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateImageList.h
# End Source File
# Begin Source File

SOURCE=.\DlgDelimiters.h
# End Source File
# Begin Source File

SOURCE=.\DlgDrawEdit.h
# End Source File
# Begin Source File

SOURCE=.\DlgDumpSettings.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditKeywords.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditorColor.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditorPrintSetup.h
# End Source File
# Begin Source File

SOURCE=.\DlgErrors.h
# End Source File
# Begin Source File

SOURCE=.\DlgFileItemName.h
# End Source File
# Begin Source File

SOURCE=.\DlgGPScintillaFind.h
# End Source File
# Begin Source File

SOURCE=.\DlgGraphCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgImageList.h
# End Source File
# Begin Source File

SOURCE=.\DlgImageMask.h
# End Source File
# Begin Source File

SOURCE=.\DlgInitComObject.h
# End Source File
# Begin Source File

SOURCE=.\DlgKeyEditor.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogin.h
# End Source File
# Begin Source File

SOURCE=.\DlgMethods.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewSession.h
# End Source File
# Begin Source File

SOURCE=.\DlgNewSpr.h
# End Source File
# Begin Source File

SOURCE=.\DlgNotepadSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgRegister.h
# End Source File
# Begin Source File

SOURCE=.\DlgScreenSize.h
# End Source File
# Begin Source File

SOURCE=.\DlgSeparateView.h
# End Source File
# Begin Source File

SOURCE=.\DlgSeparateViewInFrame.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetupSSH.h
# End Source File
# Begin Source File

SOURCE=.\DlgStatistics.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermcap.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapEsc.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapEscLine.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapKbd.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermcapTerminal.h
# End Source File
# Begin Source File

SOURCE=.\DlgTermSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewContextMenuMethods.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewFSMethods.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewInputAll.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewInputSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewIOFiles.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewItem.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewOutputSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewRegMethods.h
# End Source File
# Begin Source File

SOURCE=.\DlgViewSystemMethods.h
# End Source File
# Begin Source File

SOURCE=.\DllImport.h
# End Source File
# Begin Source File

SOURCE=.\DllServer.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\Document.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\DocumentAccessor.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\Editor.h
# End Source File
# Begin Source File

SOURCE=.\EditorPrintSettings.h
# End Source File
# Begin Source File

SOURCE=.\ErrReport.h
# End Source File
# Begin Source File

SOURCE=.\excel8.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\ExternalLexer.h
# End Source File
# Begin Source File

SOURCE=.\FilterArray.h
# End Source File
# Begin Source File

SOURCE=.\FontExt.h
# End Source File
# Begin Source File

SOURCE=.\GP_AutoSizing.h
# End Source File
# Begin Source File

SOURCE=.\GP_comm.h
# End Source File
# Begin Source File

SOURCE=.\GP_Control.h
# End Source File
# Begin Source File

SOURCE=.\GP_DlgSetting.h
# End Source File
# Begin Source File

SOURCE=.\GP_File.h
# End Source File
# Begin Source File

SOURCE=.\GP_HotKey.h
# End Source File
# Begin Source File

SOURCE=.\GP_QScroll.h
# End Source File
# Begin Source File

SOURCE=.\GP_QSort.h
# End Source File
# Begin Source File

SOURCE=.\GP_RarefiedArr.h
# End Source File
# Begin Source File

SOURCE=.\GP_RTF.h
# End Source File
# Begin Source File

SOURCE=.\GP_Term.h
# End Source File
# Begin Source File

SOURCE=.\GP_TermDoc.h
# End Source File
# Begin Source File

SOURCE=.\GP_TermView.h
# End Source File
# Begin Source File

SOURCE=.\GPAdmIsOn.h
# End Source File
# Begin Source File

SOURCE=.\GPAniButton.h
# End Source File
# Begin Source File

SOURCE=.\GPAnimate.h
# End Source File
# Begin Source File

SOURCE=.\GPAniStatic.h
# End Source File
# Begin Source File

SOURCE=.\GPAsyncSocket.h
# End Source File
# Begin Source File

SOURCE=.\GPBButton.h
# End Source File
# Begin Source File

SOURCE=.\GPButton.h
# End Source File
# Begin Source File

SOURCE=.\GPCDAODatabase.h
# End Source File
# Begin Source File

SOURCE=.\GPCDAOQueryDef.h
# End Source File
# Begin Source File

SOURCE=.\GPCDAORecordset.h
# End Source File
# Begin Source File

SOURCE=.\GPCDAOTableDef.h
# End Source File
# Begin Source File

SOURCE=.\GPCDAOWorkspace.h
# End Source File
# Begin Source File

SOURCE=.\GPCDatabase.h
# End Source File
# Begin Source File

SOURCE=.\GPChLBox.h
# End Source File
# Begin Source File

SOURCE=.\GPColorDlg.h
# End Source File
# Begin Source File

SOURCE=.\GPComboBox.h
# End Source File
# Begin Source File

SOURCE=.\GPComboBoxEx.h
# End Source File
# Begin Source File

SOURCE=.\GPCommonColorDlg.h
# End Source File
# Begin Source File

SOURCE=.\GPCommonFontDlg.h
# End Source File
# Begin Source File

SOURCE=.\GPContextMenu.h
# End Source File
# Begin Source File

SOURCE=.\GPCRecordset.h
# End Source File
# Begin Source File

SOURCE=.\GPCurrent.h
# End Source File
# Begin Source File

SOURCE=.\GPCursor.h
# End Source File
# Begin Source File

SOURCE=.\GPCursorArr.h
# End Source File
# Begin Source File

SOURCE=.\GPDateTimeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GPDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgBar.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgCommtype.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgDebug.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgFindReplace.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgNewValue.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgTelnetSet.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgViewMPVar.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgViewSpr.h
# End Source File
# Begin Source File

SOURCE=.\GPDlgViewSTable.h
# End Source File
# Begin Source File

SOURCE=.\GPDrawWnd.h
# End Source File
# Begin Source File

SOURCE=.\GPDrLBox.h
# End Source File
# Begin Source File

SOURCE=.\GPEdit.h
# End Source File
# Begin Source File

SOURCE=.\GPExcel.h
# End Source File
# Begin Source File

SOURCE=.\GPFont.h
# End Source File
# Begin Source File

SOURCE=.\GPFontList.h
# End Source File
# Begin Source File

SOURCE=.\GPFrameBar.h
# End Source File
# Begin Source File

SOURCE=.\GPFrameWnd.h
# End Source File
# Begin Source File

SOURCE=.\GPHandleArray.h
# End Source File
# Begin Source File

SOURCE=.\GPHeader.h
# End Source File
# Begin Source File

SOURCE=.\GPHTMLDocument.h
# End Source File
# Begin Source File

SOURCE=.\GPImageList.h
# End Source File
# Begin Source File

SOURCE=.\GPInputPool.h
# End Source File
# Begin Source File

SOURCE=.\GPIOFile.h
# End Source File
# Begin Source File

SOURCE=.\GPIOFileArray.h
# End Source File
# Begin Source File

SOURCE=.\GPLine.h
# End Source File
# Begin Source File

SOURCE=.\GPListBox.h
# End Source File
# Begin Source File

SOURCE=.\GPListCtr.h
# End Source File
# Begin Source File

SOURCE=.\GPMenu.h
# End Source File
# Begin Source File

SOURCE=.\GPMessage.h
# End Source File
# Begin Source File

SOURCE=.\GPMonthCalCtrl.h
# End Source File
# Begin Source File

SOURCE=.\gpmsflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\GPNotifyEdit.h
# End Source File
# Begin Source File

SOURCE=.\GPObjDialog.h
# End Source File
# Begin Source File

SOURCE=.\GPODBC_Database.h
# End Source File
# Begin Source File

SOURCE=.\GPOleDispatchDriver.h
# End Source File
# Begin Source File

SOURCE=.\GPOLEExcel1.h
# End Source File
# Begin Source File

SOURCE=.\gpolefont.h
# End Source File
# Begin Source File

SOURCE=.\GPOLERange.h
# End Source File
# Begin Source File

SOURCE=.\gppicture.h
# End Source File
# Begin Source File

SOURCE=.\GPProgress.h
# End Source File
# Begin Source File

SOURCE=.\GPReBar.h
# End Source File
# Begin Source File

SOURCE=.\GPReBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GPRegion.h
# End Source File
# Begin Source File

SOURCE=.\GPRegionArr.h
# End Source File
# Begin Source File

SOURCE=.\gprowcursor.h
# End Source File
# Begin Source File

SOURCE=.\GPScintilla.h
# End Source File
# Begin Source File

SOURCE=.\GPScreen.h
# End Source File
# Begin Source File

SOURCE=.\GPScrollBar.h
# End Source File
# Begin Source File

SOURCE=.\GPScroller.h
# End Source File
# Begin Source File

SOURCE=.\GPSlider.h
# End Source File
# Begin Source File

SOURCE=.\GPSpinButton.h
# End Source File
# Begin Source File

SOURCE=.\GPSpr.h
# End Source File
# Begin Source File

SOURCE=.\GPSprArray.h
# End Source File
# Begin Source File

SOURCE=.\GPStatic.h
# End Source File
# Begin Source File

SOURCE=.\GPStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\GPStatusBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GPTabCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GPText.h
# End Source File
# Begin Source File

SOURCE=.\GPTextArray.h
# End Source File
# Begin Source File

SOURCE=.\GPTInterface.h
# End Source File
# Begin Source File

SOURCE=.\GPToolBar.h
# End Source File
# Begin Source File

SOURCE=.\GPToolBarCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GPToolTipCtrl.h
# End Source File
# Begin Source File

SOURCE=.\GPTree.h
# End Source File
# Begin Source File

SOURCE=.\GPUnit.h
# End Source File
# Begin Source File

SOURCE=.\GPViewInput.h
# End Source File
# Begin Source File

SOURCE=.\GPViewOutput.h
# End Source File
# Begin Source File

SOURCE=.\GPwebbrowser2.h
# End Source File
# Begin Source File

SOURCE=.\GPWebBrowser2Sink.h
# End Source File
# Begin Source File

SOURCE=.\GPWindow.h
# End Source File
# Begin Source File

SOURCE=.\GPWndPropertyArray.h
# End Source File
# Begin Source File

SOURCE=.\GPWndPropertyArrayItem.h
# End Source File
# Begin Source File

SOURCE=.\GPWndSizer.h
# End Source File
# Begin Source File

SOURCE=.\GPWndSizerArr.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\Indicator.h
# End Source File
# Begin Source File

SOURCE=.\IpFrame.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\KeyMap.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\KeyWords.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\LineMarker.h
# End Source File
# Begin Source File

SOURCE=.\ListMaker.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MemUtils.h
# End Source File
# Begin Source File

SOURCE=.\MenuCustom.h
# End Source File
# Begin Source File

SOURCE=.\ssh\MISC.H
# End Source File
# Begin Source File

SOURCE=.\MSFlexGridSink.h
# End Source File
# Begin Source File

SOURCE=.\ObjectGroupsArray.h
# End Source File
# Begin Source File

SOURCE=.\ODBCRecordset.h
# End Source File
# Begin Source File

SOURCE=.\ODContext.h
# End Source File
# Begin Source File

SOURCE=.\ODContextArray.h
# End Source File
# Begin Source File

SOURCE=.\PenExt.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\Platform.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\PlatformRes.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\PropSet.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\RESearch.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GP_Term
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GP_Term
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=BRIZ
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GP_Term
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=GP_Term
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RgnExt.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\SciLexer.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\Scintilla.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\ScintillaBase.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\ScintillaWidget.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\ScintillaWin.h
# End Source File
# Begin Source File

SOURCE=.\SendPickFlProgress.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\SrvrItem.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\SString.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\Style.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\StyleContext.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\SVector.h
# End Source File
# Begin Source File

SOURCE=.\TableDataContainer.h
# End Source File
# Begin Source File

SOURCE=.\TableDataContainerItem.h
# End Source File
# Begin Source File

SOURCE=.\TermCap.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\UniConversion.h
# End Source File
# Begin Source File

SOURCE=.\UniSocket.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\ViewStyle.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\WindowAccessor.h
# End Source File
# Begin Source File

SOURCE=.\WndPrint.h
# End Source File
# Begin Source File

SOURCE=.\scintilla\XPM.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\AutoSizing.rgs
# End Source File
# Begin Source File

SOURCE=.\res\briz.bmp
# End Source File
# Begin Source File

SOURCE=.\COMImport.rgs
# End Source File
# Begin Source File

SOURCE=.\Connector.rgs
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\cursor2.cur
# End Source File
# Begin Source File

SOURCE=.\res\DevToolBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DevToolBar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\GP_Term.rc2
# End Source File
# Begin Source File

SOURCE=.\GP_Term.rgs
# End Source File
# Begin Source File

SOURCE=.\res\GP_TermDoc.ico
# End Source File
# Begin Source File

SOURCE=.\GPTInterface.rgs
# End Source File
# Begin Source File

SOURCE=.\res\H_CROSS.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_IBEAM.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_MOVE.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_NE.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_NODROP.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_NS.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_NW.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_POINT.CUR
# End Source File
# Begin Source File

SOURCE=.\res\H_WE.CUR
# End Source File
# Begin Source File

SOURCE=.\res\HO_SIZEB.CUR
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003warn.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\idr_mainwarn.ico
# End Source File
# Begin Source File

SOURCE=.\res\IToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mainfram.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Margin.cur
# End Source File
# Begin Source File

SOURCE=.\res\SepView256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SepViewDis256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar256.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleCl.rtf

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleSv.rtf

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\GP_Term.cnt

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP BASE Ignore_Default_Tool 1
# PROP Exclude_From_Build 1
# PROP Ignore_Default_Tool 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Create.ini

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\GP_Term.reg
# End Source File
# Begin Source File

SOURCE=.\LexerColors.txt
# End Source File
# Begin Source File

SOURCE=.\LexKeywords.txt
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scintilla\doc\ScintillaDoc.html

!IF  "$(CFG)" == "GP_Term - Win32 ReleaseNT"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugNT"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95ENGL"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNTENGL"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease95"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseNT"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease2000ENGL"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZRelease98ENGL"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXPENGL"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZReleaseXP"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 BRIZDebugXPENGL"

!ELSEIF  "$(CFG)" == "GP_Term - Win32 DebugXP"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "GP_Term - Win32 ReleaseXP"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\termcap.txt
# End Source File
# Begin Source File

SOURCE=.\Text1.txt
# End Source File
# Begin Source File

SOURCE=".\¬ыполненные доработки.txt"
# End Source File
# Begin Source File

SOURCE=".\план доработки.txt"
# End Source File
# End Target
# End Project
# Section GP_Term : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:GPWebBrowser2
# 	2:10:HeaderFile:GPwebbrowser2.h
# 	2:8:ImplFile:GPwebbrowser2.cpp
# End Section
# Section GP_Term : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:GPCMSFlexGrid
# 	2:10:HeaderFile:gpmsflexgrid.h
# 	2:8:ImplFile:gpmsflexgrid.cpp
# End Section
# Section GP_Term : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:GPCOleFont
# 	2:10:HeaderFile:gpolefont.h
# 	2:8:ImplFile:gpolefont.cpp
# End Section
# Section GP_Term : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:gpmsflexgrid.h
# 	2:16:DefaultSinkClass:GPCMSFlexGrid
# End Section
# Section GP_Term : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:GPwebbrowser2.h
# 	2:16:DefaultSinkClass:GPWebBrowser2
# End Section
# Section GP_Term : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:GPCPicture
# 	2:10:HeaderFile:gppicture.h
# 	2:8:ImplFile:gppicture.cpp
# End Section
# Section GP_Term : {20000012-0000-0000-0600-060054000000}
# 	1:11:IDR_GP_TERM:103
# End Section
# Section GP_Term : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:GPCRowCursor
# 	2:10:HeaderFile:gprowcursor.h
# 	2:8:ImplFile:gprowcursor.cpp
# End Section
